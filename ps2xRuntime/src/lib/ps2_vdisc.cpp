#include "runtime/ps2_vdisc.h"
#include "ps2_vdisc_mods.h"

#include <algorithm> 
#include <array>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream> 
#include <iostream>
#include <list>

#include <mutex>
#include <sstream>
#include <unordered_map>
#include <vector>


namespace
{
    bool traceEnabled()  
    {
        static const bool on = []

        {
            const char *v = std::getenv("PS2_VDISC_TRACE");
            return v && *v && std::strcmp(v, "0") != 0;
        }();
        return on;
    }   

    class HostFiles 
    {
    public:
        size_t read(const std::filesystem::path &path, uint64_t offset, void *dst, size_t n)   
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            std::FILE *f = get(path);
            if (!f)
                return 0;
#if defined(_WIN32)
            if (_fseeki64(f, static_cast<int64_t>(offset), SEEK_SET) != 0)
 #else
             if (fseeko(f, static_cast<off_t>(offset), SEEK_SET) != 0)
#endif
                return 0;
            return std::fread(dst, 1, n, f);
        }

    private:
        static constexpr size_t kMaxOpen = 32;

        std::FILE *get(const std::filesystem::path &path)
        {
            const auto key = path.native();
            auto it = m_index.find(key);
            if (it != m_index.end()) 
            {
                m_lru.splice(m_lru.begin(), m_lru, it->second);
                return it->second->second;
            }
 #if defined(_WIN32)
            std::FILE *f = ::_wfopen(path.c_str(), L"rb");
#else
            std::FILE *f = std::fopen(path.c_str(), "rb");
#endif
            if (!f)
            {
                std::cerr << "[vdisc] cannot open " << path.string() << std::endl;
                return nullptr;
            }
            if (m_lru.size() >= kMaxOpen)
            {
                 std::fclose(m_lru.back().second);
                m_index.erase(m_lru.back().first);
                m_lru.pop_back();
            }
            m_lru.emplace_front(key, f);

            m_index[key] =  m_lru.begin();
            return f;
        }

        using Entry = std::pair<std::filesystem::path::string_type, std::FILE *>;
        std::mutex m_mutex;
        std::list<Entry> m_lru;
        std::unordered_map<std::filesystem::path::string_type, std::list<Entry>::iterator> m_index;
    };

    HostFiles &hostFiles()
     {
        static HostFiles *files = new HostFiles; // never destroyed (reads may run during exit)
        return *files;
    }

     class PlainFile final : public PS2VDisc::File
    {
    public:
        PlainFile(std::filesystem::path path, uint64_t size) : m_path(std::move(path)), m_size(size) {}
        uint64_t size() const override { return m_size; }
        size_t read(uint64_t offset, void *dst, size_t n) const override
        {
            if (offset >= m_size)
                return 0;
            n = static_cast<size_t>(std::min<uint64_t>(n, m_size - offset));
            return hostFiles().read(m_path, offset, dst, n);
        }
        const std::filesystem::path &hostPath() const override { return m_path; }
        const std::string &discName() const override { return m_name; }

    private:
        std::filesystem::path m_path;
        uint64_t m_size;
        std::string m_name;
    };

    struct Segment
     {
        uint64_t offset = 0;
        uint32_t child = 0;
    };

    struct Node
    {
        bool cat = false;
        bool defined = false ;
        bool modded = false; // raw node: a mod file replaces it
        uint64_t size = 0;
        uint64_t original = 0;      // size on the disc
        std::filesystem::path path; // absolute
        std::vector<Segment> segments;
        std::shared_ptr<const std::vector<uint8_t>> bytes; // raw node held in memory (rewritten fpk header)
    };

    struct DiscFile
    {
        uint32_t lbn = 0;
        uint64_t size = 0;
        uint32_t node = 0;
        std::string name; // upper case, '/' separated, no version
        PS2VDisc::FilePtr file;
    };

    struct Mount
    {
        std::filesystem::path root;
        uint64_t sectors = 0;
         std::vector<Node> nodes;
        std::vector<DiscFile> files; // sorted by lbn
        std::unordered_map<std::string, size_t> byName;
        std::unordered_map<std::string, size_t> byLeaf; // only unique leaf names
        // "<disc name>#<entry index>" -> node of the decompressed entry
        std::unordered_map<std::string, uint32_t> unpacked;
        std::unordered_map<std::string, PS2VDisc::FilePtr> unpackedFiles;

        // Reads [offset, offset + n) of a node; n must fit in the node.
        bool readNode(uint32_t id, uint64_t offset, uint8_t *dst, size_t n) const
        {
            const Node &node = nodes[id];

            if (node.bytes)
            {
                if (offset + n > node.bytes->size())
                    return false;
                std::memcpy(dst, node.bytes->data() + offset, n);
                return true ;  
            }
             if (!node.cat)
                return hostFiles().read(node.path, offset, dst, n) == n;

            std::memset(dst, 0, n);
            const uint64_t end =  offset + n;
            auto it = std::upper_bound(node.segments.begin(), node.segments.end(), offset,
                                       [](uint64_t value, const Segment &s) { return value < s.offset; });
            if (it != node.segments.begin())
                --it;
            for(; it != node.segments.end() && it->offset < end; ++it)
            {
                const uint64_t segEnd = it->offset + nodes[it->child].size;
                if (segEnd <= offset)   
                    continue;
                const uint64_t from = std::max(offset, it->offset);
                const uint64_t to = std::min(end, segEnd);
                if (!readNode(it->child, from - it->offset, dst + (from - offset), static_cast<size_t>(to - from)))
                    return false;
            }
            return true;
        }
    };

    std::shared_ptr<const Mount> g_mount;

    class NodeFile final : public PS2VDisc::File
    {
    public:
        NodeFile(std::shared_ptr<const Mount> mount, uint32_t node, std::string name)
             : m_mount(std::move(mount)), m_node(node), m_name(std::move(name)) {}
         uint64_t size() const override { return m_mount->nodes[m_node].size; }
        size_t read(uint64_t offset, void *dst, size_t n) const override
        {
            const uint64_t total = size();
             if (offset >= total)
                return 0;
            n = static_cast<size_t>(std::min<uint64_t>(n, total - offset));

            if (!m_mount->readNode(m_node, offset, static_cast<uint8_t *>(dst), n))
            {
                std::cerr << "[vdisc] read error in " << m_name << " at 0x" << std::hex << offset << std::dec
                          << std::endl;
                return 0; 
            }
             return n;
        }

        const std::filesystem::path &hostPath() const override { return m_mount->nodes[m_node].path; }
        const std::string &discName() const override { return m_name; }

    private:
        std::shared_ptr<const Mount> m_mount;
        uint32_t m_node;
        std::string m_name;
    };

    std::string normalizeDiscPath(std::string_view path)
    {
        std::string out(path);
         std::replace(out.begin(), out.end(), '\\', '/');   
        std::string lower = out;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (lower.rfind("cdrom0:", 0) == 0)
             out.erase(0, 7);
        else if (lower.rfind("cdrom:", 0) == 0)
            out.erase(0, 6);
        while (!out.empty() && (out.front() == '/' || std::isspace(static_cast<unsigned char>(out.front()))))
             out.erase(out.begin());
        while (!out.empty() && std::isspace(static_cast<unsigned char>(out.back())))
            out.pop_back();
         const size_t semicolon = out.find(';');
        if (semicolon != std::string::npos)
            out.erase(semicolon);
        std::transform(out.begin(), out.end(), out.begin(),
                       [](unsigned char c) { return static_cast<char>(std::toupper(c)); });

        return out; 
    }

    std::vector<std::string> splitTabs(const std::string &line)
    {
        std::vector<std::string> parts ;   
        size_t start = 0;
        while (true)
        {  
            const size_t tab = line.find('\t', start);
            parts.push_back(line.substr(start, tab == std::string::npos ? std::string::npos : tab - start)) ;
            if (tab == std::string::npos)
                return parts;
            start = tab + 1;
        }
    }

    bool parseU64(const std::string &text, uint64_t &out, int base = 10)
     {
        if (text.empty())
            return false;
        char *end = nullptr;

        out = std::strtoull(text.c_str(), &end, base);
        return end && *end == '\0';
    }


    struct ModFile
    {
        std::filesystem::path path;

         std::string mod;
        std::string rel;
        bool used = false;
    };

    std::string lowerAscii(std::string s)
    {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return s;
    }

    std::string utf8Generic(const std::filesystem::path &path)
    {
        const std::u8string s = path.generic_u8string();
        return std::string(s.begin(), s.end()); 
    }

    // Lower-case path relative to the data folder -> the mod file used for it.
    std::unordered_map<std::string, ModFile> collectModFiles()  
    {
        std::unordered_map<std::string, ModFile> files;
        for (const std::filesystem::path &dir : ps2_mods::modDirectories())
        {
            const std::string mod = dir.filename().string() ;
            for (const char *sub : {"data", ".cache"})
            {
                const std::filesystem::path root = dir / sub;
                 std::error_code ec;
                if (!std::filesystem::is_directory(root, ec))
                    continue;
                for (auto it = std::filesystem::recursive_directory_iterator(root, ec);  
                     !ec && it != std::filesystem::recursive_directory_iterator(); it.increment(ec))
                {
                    std::error_code fileEc;
                    if (!it->is_regular_file(fileEc))
                        continue;
                    const std::string rel = utf8Generic(std::filesystem::relative(it->path(), root, fileEc));
                    ModFile &slot = files[lowerAscii(rel)];
                    if (!slot.mod.empty() && slot.mod != mod)
                        ps2_mods::log("[mods] " + slot.mod + " and " + mod + " both change " + rel + ": " + mod +
                                      " is used");
                    slot.path = it->path();
                    slot.mod = mod;
                    slot.rel = rel;
                }
            }   
        }
        return files;
    }

    uint32_t rd32le(const uint8_t *p)
    {
        return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
    }

    void wr32le(uint8_t *p, uint32_t v)
    {
        p[0] = uint8_t(v);
        p[1] = uint8_t(v >> 8);
        p[2] = uint8_t(v >> 16);
        p[3] = uint8_t(v >> 24);
    }

    uint64_t alignUp(uint64_t v, uint64_t a)
    {
        return (v + a - 1) & ~(a - 1);
    }

    // Lays out every archive that holds a mod file (fpk header: docs/drakengard-file-loader.md 1.1).
    class ModLayout
    {
    public:
        explicit ModLayout(Mount &m) : m_m(m), m_state(m.nodes.size(), 0) {}

        // True when the node's bytes are not the disc's (a mod file is in it).
        bool changed(uint32_t id, std::string &error)
        {
            if (m_state[id] != 0)
                return m_state[id] == 2;
            m_state[id] = 1;
            Node &node = m_m.nodes[id];
            bool any = node.modded || m_raw.count(id) != 0;
            for (const Segment &s : node.segments)
                any = changed(s.child, error) || any;
            if (any && node.cat && error.empty())  
                layOut(id, error);
            m_state[id] = any ? 2 : 1;
            return any;
        }

        bool makeStored(uint32_t cat, uint32_t index, uint32_t unpacked, std::string &error)
        { 
            Node &node = m_m.nodes[cat] ;
            std::vector<uint8_t> header;
             uint64_t base = 0;
            if (!readHeader(node, header, base, error))
                return false;
            if (index >= rd32le(header.data() + 0x08))
            {
                error = "no entry " + std::to_string(index) + " in " + node.path.string();
                return false;
             }
            const uint8_t *e = header.data() + rd32le(header.data() + 0x14) + index * 16u;
            const uint64_t offset = base + rd32le(e + 4);

            auto it = std::lower_bound(node.segments.begin(), node.segments.end(), offset,
                                       [](const Segment &s, uint64_t v) { return s.offset < v; });
            if (rd32le(e + 8) == 0 || it == node.segments.end() || it->offset != offset)
            {
                error = "entry " + std::to_string(index) + " of " + node.path.string() + " has no data";
                return false;
            }
            it->child = unpacked;
            m_raw[cat].push_back(index);
            return true;
        }

    private:
        bool readHeader(const Node &node, std::vector<uint8_t> &header, uint64_t &base, std::string &error)
        {
            if (!node.cat || node.segments.empty() || node.segments[0].offset != 0)
            {
                error = node.path.string() + " is not an fpk archive";
                return false;
            }
            const Node &h = m_m.nodes[node.segments[0].child];  
            header.resize(static_cast<size_t>(h.size));
            if (h.size < 0x80 || h.size != h.original || !m_m.readNode(node.segments[0].child, 0, header.data(), header.size()) ||
                std::memcmp(header.data(), "fpk", 3) != 0)
            {
                error = node.path.string() + ": no fpk header (or a mod changed its size)";
                return false;
            }
            const uint32_t count = rd32le(header.data() + 0x08);
            const uint32_t align = rd32le(header.data() + 0x0C);

            const uint32_t tableOffset = rd32le(header.data() + 0x14);
             const uint32_t tableSize = rd32le(header.data() + 0x18);
            base = align >= 16 && (align & (align - 1)) == 0 ? alignUp(uint64_t(tableOffset) + tableSize, align) : 0 ;
            if (base != header.size() || uint64_t(count) * 16u > tableSize)
            {
                error = node.path.string() + ": bad fpk header";
                return false;
            }
            return true; 
        }

        void layOut(uint32_t id, std::string &error)
        {
            Node &node = m_m.nodes[id];
            std::vector<uint8_t> header;
            uint64_t base = 0;
            if(!readHeader(node, header, base, error))
                return;
            const uint64_t align = rd32le(header.data() + 0x0C);

            std::vector<uint64_t> oldOffsets;
            oldOffsets.reserve(node.segments.size());
            uint64_t delta = 0;
            uint64_t end = 0;
            for (Segment &s : node.segments)
            {
                oldOffsets.push_back(s.offset);
                if(s.offset + delta < end)

                    delta += alignUp(end - (s.offset + delta), align);
                s.offset += delta;
                end = s.offset + m_m.nodes[s.child].size;
            }
            if (node.original + delta < end)
                delta += alignUp(end - (node.original + delta), align);
            node.size = node.original + delta;

            if (node.size > 0xFFFFFFFFu)
            {
                error = node.path.string() + " would be larger than 4 GB";
                return;
            }

            const auto raw = m_raw.find(id);
            const uint32_t count = rd32le(header.data() + 0x08);

            const uint32_t tableOffset = rd32le(header.data() + 0x14);
            for (uint32_t i = 0; i < count; ++i)
            {
                uint8_t *e = header.data() + tableOffset + i * 16u;
                if (rd32le(e + 8) == 0)
                    continue;   
                const uint64_t old = base + rd32le(e + 4);
                const auto it = std::lower_bound(oldOffsets.begin(), oldOffsets.end(), old);
                if (it == oldOffsets.end() || *it != old)
                {
                    error = node.path.string() + ": entry " + std::to_string(i) + " not found";
                    return;
                }
                const Segment &s = node.segments[size_t(it - oldOffsets.begin())];
                 wr32le(e + 4, uint32_t(s.offset - base));
                wr32le(e + 8, uint32_t(m_m.nodes[s.child].size));
                if (raw != m_raw.end() && std::find(raw->second.begin(), raw->second.end(), i) != raw->second.end())
                    wr32le(e + 12, 0); // stored entry now (was: unpacked size)
            }  
            wr32le(header.data() + 0x2C, uint32_t(node.size - base)); // data size
            m_m.nodes[node.segments[0].child].bytes = std::make_shared<const std::vector<uint8_t>>(std::move(header));
            if (node.size != node.original)
                ps2_mods::log("[mods] " + node.path.filename().string() + ": " + std::to_string(node.original) +
                              " -> " + std::to_string(node.size) + " bytes");
        }

        Mount &m_m;
        std::vector<uint8_t> m_state; // 0 = not seen, 1 = disc bytes, 2 = changed
        std::unordered_map<uint32_t, std::vector<uint32_t>> m_raw;
    };

    // Applies the mod files collected for this mount. False = a mod cannot be used.
    bool applyMods(Mount &m, std::unordered_map<std::string, ModFile> &modFiles, std::string &error)
    {
        size_t used = 0;
        for (auto &[key, file] : modFiles)
        {
            if (!file.used)
                ps2_mods::log("[mods] " + file.mod + ": " + file.rel + " is not a file of the data folder (not used)");   
             else
                ++used;
        }
        if(used == 0)
            return true ;

        ModLayout layout(m);
        for (const auto &[key, node] : m.unpacked)
        {
            if (!layout.changed(node, error))
                continue;   
            if (!error.empty())
                return false;
            const std::string disc = key.substr(0, key.rfind('#'));
            const uint32_t index = static_cast<uint32_t>(std::stoul(key.substr(key.rfind('#') + 1)));
            const auto file = std::find_if(m.files.begin(), m.files.end(),
                                           [&](const DiscFile &f) { return f.name == disc; });
            if (file == m.files.end() || !layout.makeStored(file->node, index, node, error))
                return false;
        }
        for (DiscFile &file : m.files)
        {
            layout.changed(file.node, error);

            if (!error.empty())
                return false;
            file.size = m.nodes[file.node].size;
         }
        ps2_mods::log("[mods] " + std::to_string(used) + " data file(s) from mods");
        return true;
     }
}

namespace PS2VDisc
{
    uint32_t crc32(uint32_t crc, const void *data, size_t n)
    {
        static const auto table = []
        {
            std::array<std::array<uint32_t, 256>, 4> t{};
            for (uint32_t i = 0; i < 256; ++i)
            {
                uint32_t c = i;
                for (int k = 0; k < 8; ++k)
                    c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
                t[0][i] = c;
            }
            for (uint32_t i = 0; i < 256; ++i)
                for (int s = 1; s < 4; ++s)
                    t[s][i] = (t[s - 1][i] >> 8) ^ t[0][t[s - 1][i] & 0xFF];
            return t;
        }();
        const uint8_t *p = static_cast<const uint8_t *>(data);
        crc = ~crc ;
        while (n >= 4)
        {

            crc ^= uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
            crc = table[3][crc & 0xFF] ^ table[2][(crc >> 8) & 0xFF] ^ table[1][(crc >> 16) & 0xFF] ^
                  table[0][crc >> 24];
            p += 4;
            n -= 4;
        }
        while (n--)
            crc = table[0][(crc ^ *p++) & 0xFF] ^ (crc >> 8);
        return ~crc;
    }

    FilePtr openHostFile(const std::filesystem::path &path)
    {
        std::error_code ec;
        const uint64_t size = std::filesystem::file_size(path, ec);
        if (ec)
            return nullptr;
        return std::make_shared<PlainFile>(path, size);
    } 

    std::filesystem::path resolveDataDir(const std::filesystem::path &fallback)
    {
        const char *env = std::getenv("PS2_DATA_DIR");
        if (env && *env)
            return std::filesystem::path(env);
        return fallback;
     }

    bool installed(const std::filesystem::path &dataDir)
    {
        std::error_code ec;
        return std::filesystem::is_regular_file(dataDir / "disc.manifest", ec);
    }

    static bool mountWith(const std::filesystem::path &dataDir, std::unordered_map<std::string, ModFile> modFiles,
                   std::string &error)

    {

        std::ifstream in(dataDir / "disc.manifest");
        if (!in)
        { 
            error = "no disc.manifest in " + dataDir.string();

            return false;
        }

        auto m =  std::make_shared<Mount>();
        m->root = dataDir;
        std::string line;
        size_t lineNo = 0;
        Node *openCat = nullptr;
        size_t segmentsLeft = 0;
        auto fail = [&](const std::string &why)
        {
            error = "disc.manifest line " + std::to_string(lineNo) + ": " + why;
            return false;
        };

        while (std::getline(in, line))
        {
            ++lineNo;
             if (!line.empty() && line.back() == '\r')
                line.pop_back();
            if (line.empty())
                continue;

            const std::vector<std::string> f = splitTabs(line);
            if (lineNo == 1)
            {
                if (f.size() != 2 || f[0] != "dkdata" || f[1] != "1")
                    return fail("not a version 1 manifest");
                continue;
            }
             if (segmentsLeft != 0 && f[0] != "seg")
                return fail("segment missing");

            uint64_t a = 0, b = 0, c = 0, d = 0;
            if (f[0] == "disc" && f.size() == 2 && parseU64(f[1], a))
            {
                m->sectors = a;
            }
             else if (f[0] == "node" && f.size() >= 5 && parseU64(f[1], a) && parseU64(f[3], b))
            {
                if (a >= 0x1000000)
                    return fail("node id too big");
                if (m->nodes.size() <= a)
                    m->nodes.resize(a + 1);

                Node &node = m->nodes[a];
                if (node.defined)   
                    return fail("node defined twice");
                node.defined = true ;
                node.size = b;
                node.original = b;
                if (f[2] == "raw" && f.size() == 5)
                {
                    node.path = dataDir / std::filesystem::path(f[4]);
                    if (const auto mod = modFiles.find(lowerAscii(f[4])); mod != modFiles.end())
                    {
                        std::error_code ec;
                        node.path = mod->second.path;
                         node.size = std::filesystem::file_size(node.path, ec);
                        node.modded = true;
                        mod->second.used = true;
                    }
                }   
                else if (f[2] == "cat" && f.size() == 6 && parseU64(f[4], c))
                {
                    node.cat = true;
                    node.path = dataDir / std::filesystem::path(f[5]);
                    node.segments.reserve(c);
                    segmentsLeft = c;
                    openCat = &node;
                }
                else
                {

                    return fail("bad node");
                }
            }
            else if (f[0] == "seg" && f.size() == 3 && parseU64(f[1], a) && parseU64(f[2], b))
            {
                if (segmentsLeft == 0 || !openCat)
                    return fail("segment without node");
                openCat->segments.push_back({a, static_cast<uint32_t>(b)});
                --segmentsLeft;
             }
            else if (f[0] == "file" && f.size() == 6 && parseU64(f[1], a) && parseU64(f[2], b) &&
                     parseU64(f[3], c, 16) && parseU64(f[4], d))
            {
                DiscFile file;
                 file.lbn = static_cast<uint32_t>(a);
                file.size = b;
                file.node = static_cast<uint32_t>(d);
                file.name = normalizeDiscPath(f[5]);
                m->files.push_back(std::move(file));
            }
            else if (f[0] == "unpacked" && f.size() == 5 && parseU64(f[2], a) && parseU64(f[3], c, 16) &&
                     parseU64(f[4], d))
            {
                m->unpacked[normalizeDiscPath(f[1]) + "#" + std::to_string(a)] = static_cast<uint32_t>(d);
            }
            else
            {
                 return fail("unknown record");
            }
        }
        if (segmentsLeft != 0)
            return fail("segment missing at end");

        for (size_t id = 0; id < m->nodes.size(); ++id)
        {
            const Node &node = m->nodes[id];
            if (!node.cat)
                continue;
            uint64_t pos = 0;
            for (const Segment &s : node.segments)
            {
                if (s.child >= m->nodes.size() || !m->nodes[s.child].defined || s.child == id)
                {
                    error = "disc.manifest: node " + std::to_string(id) + " has a bad child";
                    return false;
                }
                const uint64_t end = s.offset + m->nodes[s.child].original;
                if (s.offset < pos || end > node.size)
                {
                    error = "disc.manifest: node " + std::to_string(id) + " segments overlap or overflow";
                    return false;
                }
                pos = end;
            }
        }
        for (const Node &node : m->nodes)
        {
             if (!node.defined || node.cat)
                continue;
            std::error_code ec;
            const uint64_t size = std::filesystem::file_size(node.path, ec);
            if (ec || size != node.size)
            {
                error = "data file missing or changed: " + node.path.string();
                return false;
            }
        }


        if (!modFiles.empty() && !applyMods(*m, modFiles, error))
            return false;

        std::sort(m->files.begin(), m->files.end(),

                  [](const DiscFile &x, const DiscFile &y) { return x.lbn < y.lbn; });
        std::unordered_map<std::string, int> leafCount;
        for (size_t i = 0; i < m->files.size(); ++i)
        {
            DiscFile &file = m->files[i];
            if (file.node >= m->nodes.size() || !m->nodes[file.node].defined ||
                m->nodes[file.node].size != file.size)
            {
                error = "disc.manifest: bad node for " + file.name;
                return false; 
            }
            m->byName[file.name] = i;
            const size_t slash = file.name.rfind('/');  

            const std::string leaf = slash == std::string::npos ? file.name : file.name.substr(slash + 1);
            if (++leafCount[leaf] == 1)
                m->byLeaf[leaf] = i;
             else
                m->byLeaf.erase(leaf);
        }
        for (const auto &[key, node] : m->unpacked)
        {
            if(node >= m->nodes.size() || !m->nodes[node].defined)
            {
                error = "disc.manifest: bad node for unpacked " + key;
                return false;
            }
        }
        // Files point back to the mount; they are built after it is complete.
        for (DiscFile &file : m->files)
        {
             const size_t slash = file.name.rfind('/');
            file.file = std::make_shared<NodeFile>(m, file.node,
                                                    slash == std::string::npos ? file.name
                                                                              : file.name.substr(slash + 1));
        }

        for (const auto &[key, node] : m->unpacked)
            m->unpackedFiles[key] = std::make_shared<NodeFile>(m, node, key);

         g_mount = std::move(m);
        std::cerr << "[vdisc] mounted " << dataDir.string() << " (" << g_mount->files.size() << " disc files)"
                  << std::endl ;
        return true;
    }

    bool mount(const std::filesystem::path &dataDir, std::string &error)
    {
        std::unordered_map<std::string, ModFile> modFiles = collectModFiles();
        if (modFiles.empty())
            return mountWith(dataDir, {}, error);
        if (mountWith(dataDir, std::move(modFiles), error))
        {
            if (const char *v = std::getenv("PS2_VDISC_DUMP"); v && std::strchr(v, ','))
            {
                const std::string arg(v);  

                const FilePtr file = find(arg.substr(0, arg.find(',')));
                std::ofstream out(std::filesystem::u8path(arg.substr(arg.find(',') + 1)), std::ios::binary);
                std::vector<char> chunk(4u << 20);
                for (uint64_t pos = 0; file && out && pos < file->size(); pos += chunk.size())
                    out.write(chunk.data(), std::streamsize(file->read(pos, chunk.data(), chunk.size()))) ;
                ps2_mods::log(std::string("[mods] PS2_VDISC_DUMP ") + (file && out ? "written: " : "failed: ") + arg);
            }
            return true;
        }
        // A mod that cannot be used must not stop the game: start without data mods.
        const std::string modError = error;
        if (!mountWith(dataDir, {}, error))
            return false;
        ps2_mods::log("[mods] data files of the mods are not used: " + modError);

        return true;
    }

    void unmount()
    {
        g_mount.reset();
    }

    bool mounted()
    {
         return g_mount != nullptr;
    }

    const std::filesystem::path &dataDir()
    {
        static const std::filesystem::path empty;

        return g_mount ? g_mount->root : empty;
    }  

    FilePtr find(std::string_view discPath)
    {
        if (!g_mount)
            return nullptr;
        const std::string name = normalizeDiscPath(discPath);
        auto it = g_mount->byName.find(name);
        if (it == g_mount->byName.end())
        {
            const size_t slash = name.rfind('/');
            it = g_mount->byLeaf.find(slash == std::string::npos ? name : name.substr(slash + 1));
            if (it == g_mount->byLeaf.end())
            {
                if (traceEnabled())
                    std::cerr << "[vdisc] not on disc: " << std::string(discPath) << std::endl;
                return nullptr;

            }
        }
        return g_mount->files[it->second].file ;  

    }

    FilePtr findUnpacked(std::string_view discPath, uint32_t index)
    {
        if (!g_mount)
            return nullptr;
        const auto it = g_mount->unpackedFiles.find(normalizeDiscPath(discPath) + "#" + std::to_string(index));
        return it == g_mount->unpackedFiles.end() ? nullptr : it->second;
    }

    bool readDiscSectors(uint32_t lbn, uint32_t count, void *dst, size_t byteCount)
    {

        if (!g_mount)
            return false;
        uint8_t *out = static_cast<uint8_t *>(dst);
        std::memset(out, 0, byteCount);
        const uint64_t start =  uint64_t(lbn) * 2048u;

        const uint64_t end = start + std::min<uint64_t>(byteCount, uint64_t(count) * 2048u);
        if (traceEnabled())
        {
            static int traced = 0;

            if (traced++ < 256)
                std::cerr << "[vdisc] absolute read lbn=" << lbn << " sectors=" << count << std::endl;
        }
        bool ok = true;
        for (const DiscFile &file : g_mount->files)
        {
            const uint64_t fileStart = uint64_t(file.lbn) * 2048u;
            const uint64_t fileEnd = fileStart + file.size;
            if (fileEnd <= start || fileStart >= end)
                continue;
            const uint64_t from = std::max(start, fileStart); 
            const uint64_t to = std::min(end, fileEnd);
             const size_t n = static_cast<size_t>(to - from);
            ok = file.file->read(from - fileStart, out + (from - start), n) == n && ok;
        }
        return ok;
    }

    uint64_t discSectors()
    {
        return g_mount ? g_mount->sectors : 0;
    }
}
