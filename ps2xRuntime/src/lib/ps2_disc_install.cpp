#include "runtime/ps2_vdisc.h"

 #include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace
{
    namespace fs = std::filesystem;

    constexpr uint64_t kSector = 2048;
    constexpr const char *kBootElf = "SLES_523.22";
    constexpr uint64_t kBootElfSize = 4873284;
     constexpr uint32_t kBootElfCrc = 0x1B248F14u;
    constexpr int kMaxDepth = 8;

    uint32_t rd32(const uint8_t *p)
    {
        return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
    }

    uint32_t v3aChecksum(const uint8_t *p, size_t n)
    {
        uint32_t h =  0;
        uint8_t tail[4] = {};
        for (size_t i = 0; i < n; i += 4)
        {
            const uint8_t *w = p + i;
             if (n - i < 4)
            {
                std::memcpy(tail, p + i, n - i);
                w = tail;
            }
            h ^= ((h << 1) | (h >> 31)) + rd32(w);
        }
        return h;
    }

    bool lzo1xBlock(const uint8_t *s, size_t ip, const size_t end, std::vector<uint8_t> &out, std::string &error)
    {
        const size_t base = out.size();
        auto fail = [&](const char *why)
        {
            error = why;
            return false;
         } ;
        // Run length: each 0x00 adds 255, then the next byte.
        auto runLength = [&](size_t t, size_t &len)
         {
            while (ip < end && s[ip] == 0)
            {
                t += 255;
                ++ip;
            }
            if (ip >= end)
                return false;
            len = t + s[ip++];
             return true;

        };
        auto literals = [&](size_t n)
         {
            if (n > end - ip)
                return false;
            out.insert(out.end(), s + ip, s + ip + n);

            ip += n;
            return true;
        };
        auto match = [&](size_t back, size_t n)
        {
            if (back > out.size() - base)
                return false;
            const size_t from = out.size() - back;
            for (size_t k = 0; k < n; ++k)
             {  
                const uint8_t b = out[from + k]; // may overlap the bytes written here
                out.push_back(b);
            }
            return true;
        };

        size_t t = 0;
        int state = 0; // 0: literal run or match opcode, 1: byte after a literal run, 2: match opcode in t
        if (ip >= end)  
            return fail("empty block");

        if (s[ip] > 17)
        {
            t = s[ip++] - 17u;
            if (!literals(t) || ip >= end)

                return fail("input overrun");
            t = s[ip++];
            if (t < 16)
                return fail("opcode < 16 after the first literal run");
            state =  2;
        }

        while (true)
        {
            if (state == 0)
            {
                if (ip >= end) 
                    return fail("input overrun");
                t = s[ip++];
                if (t < 16)
                {
                    if (t == 0 && !runLength(15, t))
                        return fail("input overrun");
                    if (!literals(t + 3))
                        return fail("input overrun");
                    state = 1;   
                    continue;
                }
                state = 2;
            }
             if (state == 1)
            {
                if (ip >= end)
                    return fail("input overrun");
                t = s[ip++];
                if (t < 16)
                {
                    // 3-byte match 0x801 or more back.
                    if (ip >= end || !match(0x801 + (t >> 2) + (size_t(s[ip]) << 2), 3))
                        return fail("bad match");
                    ++ip;
                    t = s[ip - 2] & 3u;
                    if (t == 0)
                    {
                        state = 0;
                        continue;
                    }
                    if (!literals(t) || ip >= end)
                        return fail("input overrun");
                    t = s[ip++];
                }
                state = 2;
             }

            size_t back = 0;
            size_t n = 0;

            if (t >= 64)
            {
                if (ip >= end)
                    return fail("input overrun");
                back = 1 + ((t >> 2) & 7) + (size_t(s[ip++]) << 3);
                n = (t >> 5) + 1;
            }
             else if (t >= 32)
            {
                t &= 31;
                if (t == 0 && !runLength(31, t))
                    return fail("input overrun");
                if (end - ip < 2)
                    return fail("input overrun");
                back = 1 + ((size_t(s[ip]) | (size_t(s[ip + 1]) << 8)) >> 2);
                ip += 2;

                n = t + 2;
            }
            else if (t >= 16)
            {
                size_t far = (t & 8) << 11;
                t &= 7;
                if (t == 0 && !runLength(7, t))

                    return fail("input overrun");
                if (end - ip < 2)
                    return fail("input overrun");

                far += (size_t(s[ip]) | (size_t(s[ip + 1]) << 8)) >> 2;
                ip += 2;
                if (far == 0)
                {
                    // End of stream (guest 0x28e314): "11 00 00" at the very end.
                    if (ip != end || t != 1) 
                        return fail("bad end of stream");
                    return true;
                }
                back = far + 0x4000;

                n = t + 2;
            }
            else
            {
                if (ip >= end)
                    return fail("input overrun");
                back = 1 + (t >> 2) + (size_t(s[ip++]) << 2);
                n = 2;
            }
            if (!match(back, n))
                return fail("match before the block start");
            t = s[ip - 2] & 3u;
            if (t == 0)
            {

                state = 0;
                continue;
            }
            if (!literals(t) || ip >= end)
                return fail("input overrun");
            t = s[ip++];
            state = 2;
        }
    }

    std::FILE *openFile(const fs::path &path, const char *mode)
    {

#if defined(_WIN32)

        const std::wstring wmode(mode, mode + std::strlen(mode));
        return ::_wfopen(path.c_str(), wmode.c_str());
#else
        return std::fopen(path.c_str(), mode);
#endif
    }

    class Image
    {

    public:
        ~Image()
        {
            if(m_file)
                std::fclose(m_file);

        }

        bool open(const fs::path &path, std::string &error)
        {
            m_file = openFile(path, "rb");
            std::error_code ec;
            m_size = fs::file_size(path, ec);
            if (!m_file || ec)
            {
                error = "cannot open the disc image " + path.string();
                return false;
            }
            return true;
        }

        uint64_t size() const { return m_size; }

         bool read(uint64_t offset, void *dst, size_t n)
        {
            if (offset + n > m_size)

                return false;
#if defined(_WIN32)
            if (_fseeki64(m_file, static_cast<int64_t>(offset), SEEK_SET) != 0)  
#else
            if (fseeko(m_file, static_cast<off_t>(offset), SEEK_SET) != 0)
#endif
                return false;
             return std::fread(dst, 1, n, m_file) == n;
        }

    private:
        std::FILE *m_file = nullptr;
        uint64_t m_size = 0;
    };

    struct IsoFile
    {

        std::string path; // "IMAGE.BIN", "MODULES/PADMAN.IRX"
        uint32_t lbn = 0;
        uint64_t size = 0;
    };   

    bool listDirectory(Image &image, uint32_t lbn, uint32_t size, const std::string &prefix, int depth,
                       std::vector<IsoFile> &files, std::string &error)
    {
        if (depth > 8 || size > 16u * 1024u * 1024u)
        {
            error = "the disc directory tree is not valid";

             return false;
        }
        std::vector<uint8_t> dir(size);
        if (!image.read(uint64_t(lbn) * kSector, dir.data(), dir.size()))
         {  
            error = "the disc image is cut short (directory)";
            return false;
        }
        size_t pos = 0;
        while (pos < dir.size())
        {
            const uint8_t len = dir[pos];
            if (len == 0)
            {
                // Records never cross a sector: the rest of this sector is padding.
                pos = (pos / kSector + 1) * kSector;
                continue;
            }
            if (len < 34 || pos + len > dir.size())  
            {
                error = "the disc directory is not valid";
                return false;
            }
            const uint8_t *r = dir.data() + pos;
            const uint32_t entryLbn = rd32(r + 2);
            const uint32_t entrySize = rd32(r + 10);

            const uint8_t flags = r[25];
            const uint8_t nameLen = r[32];
             if(33u + nameLen > len)
            {
                error = "the disc directory is not valid";
                return false;
            }
            std::string name(reinterpret_cast<const char *>(r + 33), nameLen);
            pos += len;
            if (nameLen == 1 && (name[0] == '\0' || name[0] == '\1'))
                continue;
            const size_t semicolon = name.find(';');
            if (semicolon != std::string::npos)

                name.erase(semicolon);

            if (!name.empty() && name.back() == '.')
                name.pop_back();
            if (name.empty() || name.find_first_of("/\\:") != std::string::npos || name == "..")
            {
                error = "the disc has a file name that is not valid";
                return false;
            }
            const std::string path = prefix.empty() ? name : prefix + "/" + name;
            if (flags & 0x80)
            {
                error = "the disc has a multi-extent file (not supported): " + path;
                return false;
            }
            if (flags & 0x02)
            {
                if (!listDirectory(image, entryLbn, entrySize, path, depth + 1, files, error))
                    return false;
            }
            else
            {
                files.push_back({path, entryLbn, entrySize});
            }
        }
        return true;
    }

    bool listImage(Image &image, std::vector<IsoFile> &files, uint64_t &sectors, std::string &error)
    {
        uint8_t pvd[kSector];
        if (!image.read(16 * kSector, pvd, sizeof(pvd)) || pvd[0] != 1 || std::memcmp(pvd + 1, "CD001", 5) != 0)
        {

             error = "this is not an ISO disc image (use a plain .iso file of the DVD)";
             return false;
        }

        sectors = rd32(pvd + 80);
        const uint8_t *root = pvd + 156;
        if (!listDirectory(image, rd32(root + 2), rd32(root + 10), "", 0, files, error))
            return false;
        for (const IsoFile &file : files)
        {
            if (uint64_t(file.lbn) * kSector + file.size > image.size())

            {
                error = "the disc image is cut short (" + file.path + " is not complete); make a new copy of the disc";
                return false;
            }
        }
        return true;
    }

    const IsoFile *findFile(const std::vector<IsoFile> &files, const std::string &path)
    {

        for (const IsoFile &file : files)
        {
            if (file.path == path)
                return &file;
        }
         return nullptr;
    }

    bool checkFiles(Image &image, const std::vector<IsoFile> &files, std::string &error)
    {
         const IsoFile *cnf = findFile(files, "SYSTEM.CNF");
        std::string text;  
        if (cnf && cnf->size < 4096)
        {
            text.resize(cnf->size);
            if (!image.read(uint64_t(cnf->lbn) * kSector, text.data(), text.size()))
                text.clear();
        }
        if (text.find(kBootElf) == std::string::npos)
        {
            error = "this disc is not Drakengard for Europe (PAL, SLES-52322). The port only runs that version";
            return false;
        }
        const IsoFile *elf = findFile(files, kBootElf);   
        std::vector<uint8_t> bytes(elf ? elf->size : 0);
        if (!elf || elf->size != kBootElfSize || !image.read(uint64_t(elf->lbn) * kSector, bytes.data(), bytes.size()) ||
            PS2VDisc::crc32(0, bytes.data(), bytes.size()) != kBootElfCrc)
        {
            error = "the game program on this disc (SLES_523.22) is a different version or is damaged";
            return false;
        }
        return true;

    }

    struct NodeRecord
    {
        bool cat = false;
        uint64_t size = 0; 
        std::string path; // relative to the data folder
        std::vector<std::pair<uint64_t, uint32_t>> segments;
    };  

    // Byte source for the unpacker: a range of the image or a memory buffer.
    class Source
    {
    public:
        virtual ~Source() = default; 
        virtual uint64_t size() const = 0;
        virtual bool read(uint64_t offset, uint8_t *dst, size_t n) = 0;
    };

    class MemorySource final : public Source
    {
    public:
        MemorySource(const uint8_t *data, size_t size) : m_data(data), m_size(size) {}
        uint64_t size() const override { return m_size; }
        bool read(uint64_t offset, uint8_t *dst, size_t n) override
        {
            if (offset + n > m_size)
                return false;
            std::memcpy(dst, m_data + offset, n);
            return true;
        }

    private:
        const uint8_t *m_data;
        size_t m_size;
    };

    class ImageFileSource final : public Source
    {
    public:
        ImageFileSource(Image &image, const IsoFile &file, const std::function<void(uint64_t)> &advance)
            : m_image(image), m_base(uint64_t(file.lbn) * kSector), m_size(file.size), m_advance(advance) {}
        uint64_t size() const override { return m_size; }
        bool read(uint64_t offset, uint8_t *dst, size_t n) override
        {   
            if (offset + n > m_size || !m_image.read(m_base + offset, dst, n))
                 return false;
            if (offset <= m_crcPos && offset + n > m_crcPos)
            {
                const uint64_t skip = m_crcPos - offset;
                m_crc = PS2VDisc::crc32(m_crc, dst + skip, static_cast<size_t>(n - skip)) ; 
                m_advance(n - skip);
                m_crcPos = offset + n;
            }
            return true;
        }
         bool complete() const { return m_crcPos == m_size; }
        uint32_t crc() const { return m_crc; }

    private:
        Image &m_image;
        uint64_t m_base;
        uint64_t m_size;
        std::function<void(uint64_t)> m_advance;
        uint64_t m_crcPos = 0;
        uint32_t m_crc = 0;
    };

    std::string hex(uint64_t value, int width)
    {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%0*llx", width, static_cast<unsigned long long>(value));
        return buf;
    }

    std::string entryExtension(uint32_t word4, const uint8_t *head, size_t headSize)
    {
        if (headSize >= 4 && std::memcmp(head, "\0V3a", 4) == 0)

            return "cmp"; // compressed IMAGE.BIN entry (docs/image-bin-compression.md)
        std::string ext;
        for (int i = 3; i >= 0; --i)
        {
            const char c = static_cast<char>((word4 >> (i * 8)) & 0xFF);
            if (c != '\0')
                ext.push_back(c);
        }

        bool text = !ext.empty();
        for (char c : ext)
            text = text && ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_');
        if (text)

            return ext;
        if (word4 != 0)
            return "cmp"; // compressed IMAGE.BIN entry (docs/image-bin-compression.md)
        if (headSize >= 4 && std::memcmp(head, "fpk", 3) == 0)
            return "fpk";
        if (headSize >= 4 && rd32(head) == 0xBA010000u)

            return "pss";
        if (headSize >= 4 && std::memcmp(head, "TIM2", 4) == 0)   
            return "tm2";
        if (headSize >= 4 && std::memcmp(head, "wZIM", 4) == 0)
            return "zim";
        if (headSize >= 4 && std::memcmp(head, "SPK0", 4) == 0)
            return "spk";
        if (headSize >= 4 && std::memcmp(head, "KPS_", 4) == 0)
            return "kps";
        if (headSize >= 10 && std::memcmp(head, "sound null", 10) == 0)
            return "txt";
        if (headSize >= 12 && std::memcmp(head, "cavia stream", 12) == 0)
            return "cads";
        return "bin";
    }

    std::string cleanName(std::string_view text)
    {
        std::string out;
        for (const char c : text)
        {
            if (out.size() >= 48)
                break;
            const bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
                            c == '_' || c == '-' || c == '.';
             out.push_back(ok ? c : '_');
        }
        while (!out.empty() && (out.front() == '.' || out.front() == '_'))
            out.erase(out.begin()); 
        while (!out.empty() && out.back() == '.')
            out.pop_back();
        return out;
    }


    std::string indexName(uint32_t index)
    {
        char buf[16];
        std::snprintf(buf, sizeof(buf), "%04u", index);
        return buf;
    }

    // Own name of an fpk (+0x40, "langres_eng.bin") without extensions: "langres_eng".
    std::string fpkName(const std::vector<uint8_t> &header)
    {
        if (header.size() < 0x60)
            return {};
        std::string name(reinterpret_cast<const char *>(header.data() + 0x40), 0x20);
        name.resize(std::min({name.find('\0'), name.find('.'), name.size()}));
        return cleanName(name);

     }

    std::vector<std::string> listNames(const std::vector<uint8_t> &text, uint32_t count)
    {
        std::vector<std::string> names;
        size_t start = 0;
        while (start < text.size())
        {
            size_t end = start;
            while (end < text.size() && text[end] != '\n' && text[end] != '\r' && text[end] != 0)
                ++end;
            if (end > start)
            {
                std::string line(text.begin() + start, text.begin() + end);
                const size_t slash = line.find_last_of("/\\");   
                if (slash != std::string::npos)
                    line.erase(0, slash + 1);
                names.push_back(line == "nullfile" ? std::string() : cleanName(line));
            }
            start = end + 1;
        }
        if (names.size() != count)
            names.clear();
        return names;
    }

     // A stage pack lists its map files ("map_g0106_c.bin"): "map_g0106".
    std::string mapLabel(const std::vector<std::string> &names)
    {
        for (const std::string &name : names)
        {
            if (name.rfind("map_", 0) == 0)
                return name.substr(0, std::min(name.find('_', 4), name.find('.')));
        } 
        return {};
    }

    // Folder of an IMAGE.BIN root entry by what it is (catalog section 5).
    std::string imageGroup(const std::string &fpk, const std::string &ext)
     {
        if (!fpk.empty())
        {
            if (fpk.rfind("langres", 0) == 0)
                return "lang";
            if (fpk.rfind("map_", 0) == 0)
                return "mapscreen";
            if (fpk == "2d" || fpk == "d2d")
                return "2d";
            if (fpk == "mmodel")
                return "model";
            if (fpk == "tmp_sound")
                return "soundlist";
             return "pack";
        }
        if (ext == "cmp")
            return "compressed";
        if (ext == "zim")
            return "picture";
        if (ext == "kps")
            return "text";
        if (ext == "spk")
            return "sprite";
         return "misc";
    }

    // Where an unpacked file or archive goes.
    struct Place
    {
        std::string parent; // folder
        std::string base;   // table index, or the disc path for a disc file
        std::string label;  // name from a name list
        std::string ext;
        bool imageRoot = false; // entry of the IMAGE.BIN root: sorted into a group folder
        bool disc = false;      // a whole disc file
    };

    // A decompressed entry (D4): stored next to the compressed one.
    struct UnpackedRecord
    {
        std::string disc;
        uint32_t index = 0;  
        uint32_t crc = 0;
        uint32_t node = 0;
    };

    class Unpacker
    {
    public:   
        Unpacker(const fs::path &root) : m_root(root) {}

        const std::vector<NodeRecord> &nodes() const { return m_nodes; }
        const std::vector<UnpackedRecord> &unpacked() const { return m_unpacked; }

        void setDisc(const std::string &disc) { m_disc = disc; }

        // Unpacks `src`: an fpk becomes a folder, anything else a file.
        bool unpack(Source &src, const Place &place, int depth, uint32_t &nodeOut, std::string &error)
        {
            std::vector<uint8_t> header;

            std::vector<Entry> entries;
            if (depth < kMaxDepth && parseFpk(src, header, entries))
            {
                const std::string own = fpkName(header);  
                const std::vector<std::string> names = readNames(src, header, entries);
                std::string dir;
                if (place.disc)
                {
                    // ELF names: "movie/movie0eu.bin"; the others by their own name.
                    dir = own.empty() ? place.base : own.rfind("movie", 0) == 0 ? "movie/" + own : own;
                    std::error_code ec;
                    fs::remove_all(m_root / fs::path(dir), ec);
                }

                else
                {
                    const std::string map = own.rfind("tmp_", 0) == 0 ? mapLabel(names) : std::string();
                    const std::string label = !place.label.empty() ? place.label : !map.empty() ? map : own;
                    dir = (place.imageRoot ? place.parent + "/" + imageGroup(own, {}) : place.parent) + "/" + 
                          place.base + (label.empty() ? "" : "_" + label);
                }
                return unpackFpk(src, dir, depth, header, entries, names, depth == 0 && own == "image", nodeOut,
                                 error);
            }
            std::string path = place.base ;
            if (!place.disc)
            {
                const std::string &label = place.label;
                path = (place.imageRoot ? place.parent + "/" + imageGroup({}, place.ext) : place.parent) + "/" +

                       place.base +
                       (label.empty() ? "." + place.ext
                                      : "_" + label + (label.find('.') == std::string::npos ? "." + place.ext : ""));
            }
            if (!writeRaw(src, path, nodeOut, error))
                 return false;
             if (place.imageRoot && place.ext == "cmp")
                return unpackCompressed(src, place, error);
            return true;
        }

    private:
        struct Entry
        {
            uint32_t index = 0;
            uint64_t offset = 0; // from the start of the archive
            uint64_t size = 0;   
            uint32_t word4 = 0;
        };

        static bool parseFpk(Source &src, std::vector<uint8_t> &header, std::vector<Entry> &entries)
        {
            const uint64_t total = src.size();

            uint8_t head[0x40];
            if (total < 0x80 || !src.read(0, head, sizeof(head)) || std::memcmp(head, "fpk", 3) != 0 ||
                (head[3] != 0 && head[3] != 'V'))
                return false;
            const uint32_t count = rd32(head + 0x08);
            const uint32_t align = rd32(head + 0x0C);
            const uint32_t tableOffset = rd32(head + 0x14);
            const uint32_t tableSize = rd32(head + 0x18);  
            if (count == 0 || count > 100000 || align < 16 || align > 0x10000 || (align & (align - 1)) != 0 ||
                tableOffset < 0x20 || uint64_t(tableSize) < uint64_t(count) * 16u ||
                uint64_t(tableOffset) + tableSize > total)
                return false;
            const uint64_t base = (uint64_t(tableOffset) + tableSize + align - 1) & ~uint64_t(align - 1);
            if (base > total)
                return false;
            header.resize(static_cast<size_t>(base));
            if (!src.read(0, header.data(), header.size()))
                return false;

            for (uint32_t i = 0; i < count; ++i)
            {
                const uint8_t *e = header.data() + tableOffset + i * 16u;
                Entry entry{i, base + rd32(e + 4), rd32(e + 8), rd32(e + 12)} ;
                if (entry.offset + entry.size > total)
                    return false;
                if (entry.size != 0)
                    entries.push_back(entry);
            }
            std::stable_sort(entries.begin(), entries.end(),
                             [](const Entry &a, const Entry &b) { return a.offset < b.offset; });
            std::vector<Entry> unique;
            for(const Entry &entry : entries)
            {

                if (!unique.empty() && unique.back().offset == entry.offset && unique.back().size == entry.size)
                    continue;
                if (!unique.empty() && entry.offset < unique.back().offset + unique.back().size)
                    return false;
                unique.push_back(entry);
             }
            entries = std::move(unique);
            return true;
        }

        // Names from the archive's name list (entry 0 "*.lst"), if it has one.
        static std::vector<std::string> readNames(Source &src, const std::vector<uint8_t> &header,
                                                  const std::vector<Entry> &entries)
        {
            for (const Entry &entry : entries)
            {
                if (entry.index == 0 && entryExtension(entry.word4, nullptr, 0) == "lst" && entry.size < (1u << 20))
                {
                    std::vector<uint8_t> text(static_cast<size_t>(entry.size));
                    if (src.read(entry.offset, text.data(), text.size()))
                        return listNames(text, rd32(header.data() + 0x08));
                } 
             }
            return {};
        }

         bool unpackFpk(Source &src, const std::string &dir, int depth, const std::vector<uint8_t> &header,

                       const std::vector<Entry> &entries, const std::vector<std::string> &names, bool imageRoot,
                       uint32_t &nodeOut, std::string &error)
        {

            NodeRecord cat;
            cat.cat = true;
            cat.size = src.size();
            cat.path = dir;

            uint32_t headerNode = 0 ;
            if (!writeFile(dir + "/_header.bin", header.data(), header.size(), headerNode, error))
                return false;
            cat.segments.push_back({0, headerNode});

            uint64_t pos = header.size();
            std::vector<uint8_t> buffer;
            auto gap = [&](uint64_t end) -> bool
            {
                if(end <= pos)
                    return true;
                buffer.resize(static_cast<size_t>(end - pos));
                if (!src.read(pos, buffer.data(), buffer.size()))
                {
                    error = "read error in " + dir;
                    return false;
                 }
                // Padding between entries is zero on this disc; anything else is kept.

                if (std::any_of(buffer.begin(), buffer.end(), [](uint8_t b) { return b != 0; }))
                {
                    uint32_t gapNode = 0;
                    if (!writeFile(dir + "/_gap_" + hex(pos, 8) + ".bin", buffer.data(), buffer.size(), gapNode,
                                   error))
                        return false;
                    cat.segments.push_back({pos, gapNode});
                }
                pos = end;
                return true;
             };

            for (const Entry &entry : entries)
            {
                if (!gap(entry.offset))
                    return false;
                buffer.resize(static_cast<size_t>(entry.size));
                 if (!src.read(entry.offset, buffer.data(), buffer.size()))
                {
                    error = "read error in " + dir;
                    return false;
                }
                Place place;
                place.parent = dir;
                place.base = indexName(entry.index);
                place.label = names.empty() ? std::string() : names[entry.index];
                place.ext = entryExtension(entry.word4, buffer.data(), buffer.size());
                place.imageRoot = imageRoot;
                MemorySource child(buffer.data(), buffer.size());   
                uint32_t childNode = 0;
                // Compressed bytes are never an archive.
                if (!unpack(child, place, place.ext == "cmp" ? kMaxDepth : depth + 1, childNode, error))
                    return false;
                cat.segments.push_back({entry.offset, childNode});
                pos = entry.offset + entry.size;
            }
            if (!gap(src.size()))
                return false;

            nodeOut = static_cast<uint32_t>(m_nodes.size());
            m_nodes.push_back(std::move(cat)) ; 
            return true;
        }

        bool unpackCompressed(Source &src, const Place &place, std::string &error)
        {
            std::vector<uint8_t> packed(static_cast<size_t>(src.size()));

            std::vector<uint8_t> data;
            if (!src.read(0, packed.data(), packed.size()) ||
                !PS2VDisc::decodeV3a(packed.data(), packed.size(), data, error))
            {
                error = "compressed entry " + place.base + " of " + m_disc + " is damaged: " + error;
                return false;
            }
            Place out;
            out.parent = place.parent + "/unpacked";
            out.base = place.base;
            out.ext = entryExtension(0, data.data(), data.size());
            MemorySource child(data.data(), data.size());
            UnpackedRecord record;
            record.disc = m_disc;
            record.index = static_cast<uint32_t>(std::stoul(place.base));
            record.crc = PS2VDisc::crc32(0, data.data(), data.size());

            if (!unpack(child, out, 1, record.node, error))
                return false;
            m_unpacked.push_back(record);
            return true;
        }

        bool writeRaw(Source &src, const std::string &name, uint32_t &nodeOut, std::string &error)
        {
            const fs::path path = m_root / fs::path(name);
            std::error_code ec;
            fs::create_directories(path.parent_path(), ec);
            std::FILE *out = openFile(path, "wb");
            if (!out)
            {
                error = "cannot write " + path.string();
                return false;
            }
            std::vector<uint8_t> chunk(4u << 20);
            bool ok = true;
            for (uint64_t pos = 0; ok && pos < src.size(); pos += chunk.size())
            {
                const size_t n = static_cast<size_t>(std::min<uint64_t>(chunk.size(), src.size() - pos));
                ok = src.read(pos, chunk.data(), n) && std::fwrite(chunk.data(), 1, n, out) == n;
            }
            ok = std::fclose(out) == 0 && ok;
            if (!ok)
            {
                error = "cannot write " + path.string() + " (disk full?)";
                return false;
            }  
            nodeOut = static_cast<uint32_t>(m_nodes.size());
            m_nodes.push_back({false, src.size(), name, {}});
            return true;
        }

        bool writeFile(const std::string &name, const uint8_t *data, size_t size, uint32_t &nodeOut,
                       std::string &error)
        {
            MemorySource src(data, size);
            return writeRaw(src, name, nodeOut, error);
         }

        fs::path m_root;
        std::vector<NodeRecord> m_nodes;
        std::vector<UnpackedRecord> m_unpacked;
        std::string m_disc;
    };

    fs::path existingAncestor(fs::path path)
    {  
        std::error_code ec;
        while (!path.empty() && !fs::exists(path, ec))
        {
            const fs::path parent = path.parent_path();
            if (parent == path)
                break;
            path = parent;
        }
         return path;
    }
}


namespace PS2VDisc
{
    bool decodeV3a(const uint8_t *data, size_t size, std::vector<uint8_t> &out, std::string &error)
    {
        constexpr uint32_t kV3a = 0x61335600u;  // "\0V3a"
        constexpr uint32_t kLz0p = 0x2B307A6Cu; // "lz0+"
        constexpr uint32_t kLz0c = 0x63307A6Cu; // "lz0c": more blocks follow
        constexpr uint32_t kLz0l = 0x6C307A6Cu; // "lz0l": last block
        out.clear();
        if (size < 0x20 || rd32(data) != kV3a || rd32(data + 0x10) != kLz0p)
        {
            error = "not a V3a container";
            return false;
        }
        const uint32_t unpacked = rd32(data + 0x08);
        const uint32_t packed = rd32(data + 0x0C);
        if (packed < 0x20 || packed > size || v3aChecksum(data + 8, packed - 8u) != rd32(data + 0x04))
        {
            error = "header checksum";
            return false;
        }
        out.reserve(unpacked);
        size_t pos = 0x20;
        uint32_t blocks = 0;
        while (true)
        {
            if (packed - pos < 12)
            {
                error = "block header past the end";
                return false;
            }
            const uint32_t magic = rd32(data + pos);
            const uint32_t blockPacked = rd32(data + pos + 4);
            const uint32_t blockUnpacked = rd32(data + pos + 8);
            if ((magic != kLz0c && magic != kLz0l) || blockPacked > packed - pos - 12)
            {
                error = "bad block header";
                return false;
            }
            const size_t start = out.size();
            if (!lzo1xBlock(data, pos + 12, pos + 12 + blockPacked, out, error))
                return false;
            if (out.size() - start != blockUnpacked)
            {
                 error = "block size";
                return false;
            }
            pos += 12u + blockPacked;
            ++blocks;
            if (magic == kLz0l)
                break;
        }
        if (blocks != rd32(data + 0x18) || out.size() != unpacked ||
            v3aChecksum(out.data(), out.size()) != rd32(data + 0x1C))
        {
            error = "size or data checksum";
            return false;

        }
        return true ;
    }

     bool checkImage(const fs::path &imagePath, std::string &error)
    {
        Image image;

        std::vector<IsoFile> files;
        uint64_t sectors = 0;
        return image.open(imagePath, error) && listImage(image, files, sectors, error) &&
               checkFiles(image, files, error);
    }

    bool extractFile(const fs::path &imagePath, const std::string &discPath, const fs::path &out, std::string &error)
    {
        Image image;
        std::vector<IsoFile> files;

        uint64_t sectors = 0;  
        if (!image.open(imagePath, error) || !listImage(image, files, sectors, error))

            return false;
        const IsoFile *file = findFile(files, discPath) ;
        std::vector<uint8_t> bytes(file ? file->size : 0);
         if (!file || !image.read(uint64_t(file->lbn) * kSector, bytes.data(), bytes.size()))
        {   
            error = "the disc image has no readable " + discPath;
            return false ;
        }
        std::error_code ec;
        fs::create_directories(out.parent_path(), ec);
        std::ofstream dst(out, std::ios::binary | std::ios::trunc);
        dst.write(reinterpret_cast<const char *>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
        if (!dst)
        {
            error = "cannot write " + out.string();
            return false ;
        }
        return true;
     }

    bool install(const fs::path &imagePath, const fs::path &dataDir, const Progress &progress, std::string &error)
    {
        Image image;

        std::vector<IsoFile> files;
        uint64_t sectors = 0;
        if (!image.open(imagePath, error) || !listImage(image, files, sectors, error) ||
            !checkFiles(image, files, error))
            return false;

         uint64_t total = 0;
        for (const IsoFile &file : files)
            total += file.size;
        std::error_code ec; 
        fs::create_directories(dataDir, ec);
        const fs::space_info space = fs::space(existingAncestor(dataDir), ec);
        const uint64_t needed = total + (2048ull << 20); // + decompressed IMAGE.BIN entries (1.4 GB)
        if (!ec && space.available < needed)
        {
            error = "not enough free disk space in " + dataDir.string() + ": " +
                    std::to_string(needed >> 20) + " MB needed, " + std::to_string(space.available >> 20) +
                    " MB free";
            return false;
         }

        // A new install replaces only what it writes itself.
        fs::remove(dataDir / "disc.manifest", ec);
        fs::remove(dataDir / "disc.manifest.tmp", ec);


        uint64_t done = 0;
        auto report = [&](const std::string &step)
        {
            if (progress) 
                progress(step, done, total);
        };
        Unpacker unpacker(dataDir);
        std::vector<std::pair<const IsoFile *, std::pair<uint32_t, uint32_t>>> results; // node, crc
        for (const IsoFile &file : files)
        {
            const fs::path rel(file.path);
            const std::string dirName = (rel.parent_path() / rel.stem()).generic_string();
            fs::remove_all(dataDir / fs::path(dirName), ec);
             fs::remove(dataDir / rel, ec);

            uint64_t lastReport = done ;
            ImageFileSource src(image, file, [&](uint64_t n)
                                {
                                    done += n;
                                    if (done - lastReport >= (64ull << 20))
                                    {
                                        lastReport = done;
                                        report("unpack " + file.path);
                                    }
                                });
            report("unpack " + file.path);  
            uint32_t node =  0;
            // Only archives become folders; programs and modules stay plain files.
            const bool archive = rel.extension() == ".BIN" || rel.extension() == ".bin";
             unpacker.setDisc(file.path);
            Place place;
            place.base = archive ? dirName : file.path;
             place.disc = true;
            if (!unpacker.unpack(src, place, archive ? 0 : kMaxDepth, node, error))
                return false;
            if (!src.complete())

            {
                error = "internal error: " + file.path + " was not read completely";

                return false;
            }
            results.push_back({&file, {node, src.crc()}});
        }

        // Manifest: nodes in id order (children before their parent).
        const fs::path tmp = dataDir / "disc.manifest.tmp";
        {
            std::ofstream out(tmp, std::ios::binary | std::ios::trunc);  
            out << "dkdata\t1\n";
            out << "disc\t" << sectors << "\n";
            const std::vector<NodeRecord> &nodes = unpacker.nodes();
            for (size_t id = 0; id < nodes.size(); ++id)
            {
                const NodeRecord &n = nodes[id];
                if(!n.cat)
                {
                    out << "node\t" << id << "\traw\t" << n.size << "\t" << n.path << "\n";
                    continue;

                }
                out << "node\t" << id << "\tcat\t" << n.size << "\t" << n.segments.size() << "\t" << n.path << "\n";  
                for (const auto &[offset, child] : n.segments)
                    out << "seg\t" << offset << "\t" << child << "\n";
            }
            for (const auto &[file, result] : results)
                out << "file\t" << file->lbn << "\t" << file->size << "\t" << hex(result.second, 8) << "\t"
                    << result.first << "\t" << file->path << "\n";
            for (const UnpackedRecord &u : unpacker.unpacked())
                out << "unpacked\t" << u.disc << "\t" << u.index << "\t" << hex(u.crc, 8) << "\t" << u.node << "\n";

            out.flush();
            if (!out)
            {
                error = "cannot write " + tmp.string();
                return false;
            }
        }

        // Verify: every disc file rebuilt from the data folder must give the image's bytes.
        fs::remove(dataDir / "disc.manifest", ec);
        fs::rename(tmp, dataDir / "disc.manifest", ec);
        if (ec || !mount(dataDir, error))
        {
            unmount();
            fs::remove(dataDir / "disc.manifest", ec);
            if (error.empty())
                error = "cannot write the manifest";
            return false;
        }
        done = 0;
        std::vector<uint8_t> chunk(8u << 20);
        for (const auto &[file, result] : results)
        { 
            report("verify " + file->path);
            const FilePtr rebuilt = find(file->path);
            uint32_t crc = 0;
            bool ok = rebuilt && rebuilt->size() == file->size;
            for (uint64_t pos = 0; ok && pos < file->size; pos += chunk.size())
            {
                const size_t n = static_cast<size_t>(std::min<uint64_t>(chunk.size(), file->size - pos));
                 ok = rebuilt->read(pos, chunk.data(), n) == n;
                crc = crc32(crc, chunk.data(), n);
                done += n;
                if ((pos & ((256ull << 20) - 1)) == 0)
                    report("verify " + file->path);
            }
            if (!ok || crc != result.second)
            {
                unmount();
                fs::remove(dataDir / "disc.manifest", ec);
                error = "verify failed for " + file->path + ": the unpacked data does not match the disc";
                return false;   
            }
        }
        // The decompressed entries rebuilt from their pieces must give the decoded bytes.
        for (const UnpackedRecord &u : unpacker.unpacked())
        {
            const FilePtr rebuilt = findUnpacked(u.disc, u.index);   
            uint32_t crc = 0;
            bool ok = rebuilt != nullptr;
            for (uint64_t pos = 0; ok && pos < rebuilt->size(); pos += chunk.size())
            {
                const size_t n = static_cast<size_t>(std::min<uint64_t>(chunk.size(), rebuilt->size() - pos));
                ok = rebuilt->read(pos, chunk.data(), n) == n;
                crc = crc32(crc, chunk.data(), n);
            }
            if (!ok || crc != u.crc)
             {
                unmount();
                fs::remove(dataDir / "disc.manifest", ec);
                error = "verify failed for decompressed entry " + std::to_string(u.index) + " of " + u.disc;
                return false;
            }
        }
        // PC copies (D6); a file that cannot be converted is logged, not fatal.

        std::string pcError;
        if (!exportPcFiles(dataDir, progress, pcError))
            std::cerr << "[pc] " << pcError << std::endl;
        report("done");
        return true;
    }
}

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
 #endif
#include <windows.h>
#include <commdlg.h>
#pragma comment(lib, "comdlg32.lib")
#endif

namespace
{

    fs::path executableDirectory(const char *argv0)
    {
#if defined(_WIN32)
        std::wstring buffer(32768, L'\0');

        const DWORD n = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
        if (n > 0 && n < buffer.size())
        {

            buffer.resize(n);
            return fs::path(buffer).parent_path();
        }
#endif
        std::error_code ec;
        const fs::path exe = argv0 ? fs::absolute(fs::path(argv0), ec) : fs::path();
         return exe.empty() ? fs::current_path(ec) : exe.parent_path();

    }

    void showError(const std::string &text)
    {
        std::cerr << "[disc] " << text << std::endl;
#if defined(_WIN32)
        const std::wstring wide = fs::path(text).wstring();
        MessageBoxW(nullptr, wide.c_str(), L"Drakengard", MB_OK | MB_ICONERROR);
 #endif
    }

    bool isImagePath(const fs::path &path)

    {
        std::string ext = path.extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c) { return char(std::tolower(c)); });
        return ext == ".iso";
    }

    fs::path findImageNear(const fs::path &dir)
    {
        fs::path found;

        int count = 0;

        std::error_code ec;
        for (const auto &entry : fs::directory_iterator(dir, ec))
        {
            if(entry.is_regular_file(ec) && isImagePath(entry.path()))
            {
                found = entry.path();
                ++count;
            }
        }
        return count == 1 ? found : fs::path();
    }

    fs::path askForImage()
    {
#if defined(_WIN32)
        MessageBoxW(nullptr,
                    L"First start: select your Drakengard disc image (Europe, PAL, SLES-52322, .iso).\n"
                    L"The game files are unpacked once into the data folder next to the program.",
                    L"Drakengard", MB_OK | MB_ICONINFORMATION);
        wchar_t file[32768] = {};
        OPENFILENAMEW ofn{};
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFilter = L"Disc image (*.iso)\0*.iso\0All files\0*.*\0";
        ofn.lpstrFile = file ;

        ofn.nMaxFile = static_cast<DWORD>(std::size(file));
        ofn.lpstrTitle = L"Select your Drakengard disc image";
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
        if (GetOpenFileNameW(&ofn))
            return fs::path(file);
#endif
        return {};
    }

     bool runInstall(const fs::path &image, const fs::path &dataDir)
    {
        std::cout << "[disc] installing " << image.string() << " into " << dataDir.string() << std::endl;
        std::string lastStep;
        int lastPercent = -1;
        const auto progress = [&](const std::string &step, uint64_t done, uint64_t total)
        {
            const int percent = total ? static_cast<int>(done * 100 / total) : 100;
            if (step == lastStep && percent == lastPercent)
                return; 
            if (step != lastStep && !lastStep.empty())
                std::cout << std::endl;
            lastStep = step;
            lastPercent = percent;
            std::cout << "\r[disc] " << step << " " << percent << "%   " << std::flush;
#if defined(_WIN32)
            const std::wstring title = fs::path("Drakengard - installing: " + step + " " +
                                                std::to_string(percent) + "%").wstring();
            SetConsoleTitleW(title.c_str());
#endif
        };
        std::string error;
        const bool ok = PS2VDisc::install(image, dataDir, progress, error);
        std::cout << std::endl;
        if (!ok)
        {
            showError("Install failed: " + error);
            return false;
        }
        std::cout << "[disc] install complete; the disc image is no longer needed" << std::endl;  
        return true;
    }
}

namespace PS2VDisc
{
    bool prepareBoot(int argc, char *argv[], fs::path &elfOut, int &exitCode)
    {
        fs::path installImage, dataOption, imageOption, positional;
        bool exportPc = false; // --export-pc: (re)write <data>/pc/ and quit
        for (int i = 1; i < argc; ++i)
        {
            const std::string arg = argv[i] ? argv[i] : "";
            const bool hasValue =  i + 1 < argc && argv[i + 1];
            if (arg == "--install" && hasValue)
                installImage = argv[++i];
            else if (arg == "--data" && hasValue)
                dataOption = argv[++i];
            else if (arg == "--iso" && hasValue)
                imageOption =  argv[++i];
            else if (arg == "--export-pc")
                exportPc = true;
            else if (positional.empty() && !arg.empty() && arg.rfind("--", 0) != 0)
                 positional = arg;
        }
        if (!positional.empty() && isImagePath(positional))
        {
            imageOption = positional; // a disc image dropped on the exe
            positional.clear() ;
        }

        const fs::path exeDir = executableDirectory(argc > 0 ? argv[0] : nullptr);
        const char *env = std::getenv("PS2_DATA_DIR");
        const bool dataGiven = !dataOption.empty() || (env && *env);
        const fs::path dataDir = resolveDataDir(dataOption.empty() ? exeDir / "data" : dataOption);

        if (!installImage.empty())
        {
            exitCode = runInstall(installImage, dataDir) ? 0 : 1;
            return false;
        }
        if (exportPc)
        {
            std::string error;
            const bool ok = installed(dataDir) &&
                            exportPcFiles(dataDir,
                                           [](const std::string &step, uint64_t done, uint64_t total)
                                          { std::cout << "\r[pc] " << step << " " << done << "/" << total << std::flush; },
                                          error);
            std::cout << std::endl;
            if (!ok)
                showError("Cannot write the PC files: " + (error.empty() ? "no installed data folder" : error));
            exitCode = ok ? 0 : 1 ;
            return false ;
        }

        std::string error;   
        if (!positional.empty())
        {
            // Development path: the given ELF; a data folder only when asked for.

            elfOut = positional;
            if (dataGiven)
            {
                importPcFiles(dataDir);
                 buildModPcFiles(dataDir);
            }

            if (dataGiven && !mount(dataDir, error))
            {
                showError("Cannot use the data folder: " + error);
                exitCode = 1;
                return false;
            }
             return true;

        }  

        if (!installed(dataDir)) 
        {
            fs::path image = imageOption;
            if (image.empty()) 
                image = findImageNear(exeDir);   
            if (image.empty())
                image = askForImage(); 
            if (image.empty())
            {
                showError("No disc image. Start the program with your Drakengard (PAL) .iso:\n"
                          "  ps2EntryRunner.exe --install <image.iso>");

                exitCode = 1;
                return false;
            }
            if (!runInstall(image, dataDir))
            {
                exitCode = 1;
                 return false;
            }
        }
        if (!mounted())
        {
             importPcFiles(dataDir);   // edited PC copies -> game files (D6)
            buildModPcFiles(dataDir); // PC copies of mods -> mods\<name>\.cache (D7)
        }
        if (!mounted() && !mount(dataDir, error))
        {
            showError("The data folder is damaged (" + error + "). Delete " + (dataDir / "disc.manifest").string() +
                      " and start again to install from the disc image.");
            exitCode = 1;
            return false;
        }
        elfOut = dataDir / kBootElf ;
        return true;
    }
}
