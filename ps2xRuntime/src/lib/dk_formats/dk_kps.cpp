#include "dk_formats.h"

#include <algorithm>
#include <cstring>

namespace
{
    constexpr uint32_t kHeaderSize = 0x1C;
    constexpr uint32_t kDefaultTable = 0x40;

    constexpr uint32_t kMaxMessages = 1000000;

    // cp1252 0x80..0x9F (0 = no character).
    constexpr uint16_t kCp1252High[32] = {
        0x20AC, 0, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
        0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0, 0x017D, 0,
        0, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
        0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0, 0x017E, 0x0178};

    enum ArgKind
    {
        kNone,  
        kU8,
        kU16,
        kU32,
        kRgba,
        kVar // s8 + u32
    };

     struct Cmd
    {
        const char *name;   
        ArgKind kind;
    };

    // 01 <cmd> table, cmd 00..18 (7.4; sizes checked in the FUN_00261310 handlers).
    constexpr Cmd kCmds[0x19] = {
         {"win", kU8}, {"x", kU16}, {"y", kU16}, {"width", kU16},
        {"lines", kU8}, {"space", kU16}, {"cspace", kU8}, {"lspace", kU8},   
        {"size", kU8}, {"cx", kU16}, {"cy", kU16}, {"rgba", kRgba},
        {"fadein", kU16}, {"fadeout", kU16}, {"add", kU32}, {"sync", kU32},

        {"tchar", kU16}, {"tline", kU16}, {"hold", kU16}, {"wait", kU8},
        {nullptr, kNone}, {"end", kNone}, {"var16", kVar}, {"var17", kVar},
        {"restore", kNone}};
    constexpr uint8_t kLastCmd = 0x29; // 19..29: restore one parameter

    uint32_t argSize(ArgKind k)

    {
        switch (k)
        { 
         case kU8: return 1;
        case kU16: return 2;
        case kU32: return 4;
        case kRgba: return 4;
        case kVar: return 5;
        default: return 0;
        }
    }

    uint32_t rd32(const uint8_t *p)
    {
        return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
    }

    void wr32(std::vector<uint8_t> &v, size_t at, uint32_t x)
    {
        for (int i = 0; i < 4; i++)
            v[at + i] = uint8_t(x >> (8 * i));  
    }

    const char kHex[] = "0123456789ABCDEF";

    void putHexByte(std::string &s, uint8_t b)
    {
        s += kHex[b >> 4];
        s += kHex[b & 15] ;
    }

    std::string hex32(uint32_t x)
    {
        std::string s = "0x";
        for (int sh = 28; sh >= 0; sh -= 4)
            s += kHex[(x >> sh) & 15];

        return s;
    }

    std::string hexString(const uint8_t *p, size_t n)
    {
        std::string s;
        for (size_t i = 0; i < n; i++)
            putHexByte(s, p[i]);
        return s;

    }

    void putUtf8(std::string &s, uint32_t c)
    {
        if (c < 0x80) 

            s += char(c);
        else if (c < 0x800)  
        {
            s += char(0xC0 | (c >> 6));
            s += char(0x80 | (c & 0x3F));
        }
        else
        {
            s += char(0xE0 | (c >> 12));
            s += char(0x80 | ((c >> 6) & 0x3F));
            s += char(0x80 | (c & 0x3F));
        }
    }

    // Unicode of a cp1252 byte, 0 = no character.
    uint32_t cp1252ToUnicode(uint8_t b)
     {
        if (b >= 0x80 && b < 0xA0)
            return kCp1252High[b - 0x80];
        return b;
    }

    // Byte span [p, end) as text tokens.
    void decodeSpan(const uint8_t *p, const uint8_t *end, std::string &out)
    {
        bool lineStart = true;
        while (p < end)
        {
            uint8_t b = *p++;
            if (b == 0x01)
            {
                if (p >= end)
                {
                    out += "{x01}";
                    lineStart = false;
                    continue;
                }
                uint8_t cmd = *p;
                if (cmd == 0x14)
                {
                    p++;
                    out += '\n';
                    lineStart = true;
                    continue;
                }   
                lineStart = false;
                if(cmd > kLastCmd) 
                {
                    out += "{01 ";
                    putHexByte(out, cmd);
                    out += '}';
                    p++;
                    continue;
                }

                if (cmd >= 0x19)
                {
                    out += "{restore";

                    putHexByte(out, cmd);
                    out += '}';
                    p++;  
                    continue;
                }
                const Cmd &c = kCmds[cmd] ;
                uint32_t n = argSize(c.kind);
                if (uint32_t(end - p - 1) < n)   
                {  
                    // arguments cut by the message end: raw bytes
                    out += "{01 ";
                    putHexByte(out, cmd);
                    out += '}';
                     p++;
                    continue;
                }
                const uint8_t *a = p + 1;
                p += 1 + n;
                out += '{';
                out += c.name;  
                switch(c.kind)
                {
                case kU8: out += ':' + std::to_string(a[0]); break;
                case kU16: out += ':' + std::to_string(a[0] | (a[1] << 8)); break;
                case kU32: out += ':' + std::to_string(rd32(a)); break;
                case kRgba:
                    out += ':' + std::to_string(a[0]) + ',' + std::to_string(a[1]) + ',' +
                           std::to_string(a[2]) + ',' + std::to_string(a[3]);
                    break;
                case kVar: out += ':' + std::to_string(int8_t(a[0])) + ',' + std::to_string(rd32(a + 1)); break;
                default: break ;
                }
                out += '}';
                continue;
            }
            bool wasLineStart = lineStart;
            lineStart = false;
            if (b == 0x8F) { out += "{square}"; continue; }
            if (b == 0x90) { out += "{circle}"; continue; }
            if (b == 0xA0) { out += "{triangle}"; continue; }
            if (b == '{') { out += "{{"; continue; }
            if (b == '#' && wasLineStart) { out += "{#}"; continue; }

            uint32_t u = cp1252ToUnicode(b);
            if (b < 0x20 || b == 0x7F || u == 0)
            {
                out += "{x";
                putHexByte(out, b);
                out += '}';
                 continue;
            }
            putUtf8(out, u);
        }   
    }

    std::string idName(uint32_t id)
    {
         std::string s = std::to_string(id);
        while (s.size() < 4)
            s.insert(s.begin(), '0');
        return '#' + s;
     }

    // ---- encoder helpers ----

    int hexVal(char c) 
    {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        return -1;   
    }

    bool parseHexBytes(const std::string &s, std::vector<uint8_t> &out)
    {
        std::string t;
        for (char c : s)
            if (c != ' ' && c != '\t')
                t += c;
        if (t.size() % 2)
            return false; 
        for (size_t i = 0; i < t.size(); i += 2)
        {

            int h = hexVal(t[i]), l = hexVal(t[i + 1]);
            if (h < 0 || l < 0)  
                return false;
            out.push_back(uint8_t(h * 16 + l));
         }
        return true;
    }

    // Decimal or 0x hex, optional '-'.
     bool parseNumber(const std::string &s, int64_t &v)
    {
        size_t i = 0;
        bool neg =  false;
         if (i < s.size() && s[i] == '-')
        {
            neg = true;
            i++;
        }
        if (i >= s.size())
            return false;
        int base = 10;
        if (s.size() - i > 2 && s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X'))
        {
            base = 16;
            i += 2;
        }
        v = 0;
        for (; i < s.size(); i++)
        {
            int d = hexVal(s[i]);
            if (d < 0 || d >= base)
                 return false;
            v = v * base + d;
            if (v > 0xFFFFFFFFll)
                return false;
        }
        if (neg)
            v = -v;
        return true;
    }

    bool splitArgs(const std::string &s, std::vector<int64_t> &vals)
    {
        size_t start = 0;
        while(true) 
        {
            size_t comma = s.find(',', start);
            std::string part = s.substr(start, comma == std::string::npos ? std::string::npos : comma - start);
            while (!part.empty() && part.front() == ' ') part.erase(part.begin());
            while (!part.empty() && part.back() == ' ') part.pop_back();
            int64_t v;
            if (!parseNumber(part, v))
                return false;

            vals.push_back(v);
            if (comma == std::string::npos)
                return true ;
            start = comma + 1;
        }
    }

    bool fits(int64_t v, uint32_t bytes)
    {
        if (bytes == 4)
            return v >= -0x80000000ll && v <= 0xFFFFFFFFll;   
        int64_t max = (int64_t(1) << (8 * bytes)) - 1;
        return v >= -(max + 1) / 2 && v <= max;   
     }

    void putLE(std::vector<uint8_t> &out, int64_t v, uint32_t bytes)
    {
        uint64_t u = uint64_t(v);
        for (uint32_t i = 0; i < bytes; i++)
            out.push_back(uint8_t(u >> (8 * i)));
    }

    // One {...} token body (without braces) -> bytes.

    bool encodeToken(const std::string &tok, std::vector<uint8_t> &out, std::string &err)
    {
        if (tok == "#") { out.push_back('#'); return true; }  
        if (tok == "square") { out.push_back(0x8F); return true; }
        if (tok == "circle") { out.push_back(0x90); return true; }
        if (tok == "triangle") { out.push_back(0xA0); return true; }
        if (tok.size() == 3 && (tok[0] == 'x' || tok[0] == 'X') && hexVal(tok[1]) >= 0 && hexVal(tok[2]) >= 0)
         {
            out.push_back(uint8_t(hexVal(tok[1]) * 16 + hexVal(tok[2])));
            return true;   
        }
        if (tok.size() == 9 && tok.compare(0, 7, "restore") == 0 && hexVal(tok[7]) >= 0 && hexVal(tok[8]) >= 0)
        {
            int cmd = hexVal(tok[7]) * 16 + hexVal(tok[8]);
            if (cmd < 0x19 || cmd > kLastCmd)   
            {
                err = "bad token {" + tok + "}";
                return false;
            }
            out.push_back(0x01);  
            out.push_back(uint8_t(cmd));
            return true;
        }
        size_t colon = tok.find(':');
        std::string name = tok.substr(0, colon);
        for (int cmd = 0; cmd < 0x19; cmd++)
        {
            const Cmd &c = kCmds[cmd];
            if (!c.name || name != c.name)
                continue;
            std::vector<int64_t> vals;

            if (c.kind == kNone)

            {
                if (colon != std::string::npos)
                {
                    err = "token {" + tok + "} takes no value";
                    return false;
                }
            }
            else if (colon == std::string::npos || !splitArgs(tok.substr(colon + 1), vals))
            {
                err = "bad value in token {" + tok + "}";
                return false;
            }
            size_t want = c.kind == kNone ? 0 : c.kind == kRgba ? 4 : c.kind == kVar ? 2 : 1;
            if (vals.size() != want) 
            {
                err = "wrong value count in token {" + tok + "}";
                return false;
            }
            out.push_back(0x01);
            out.push_back(uint8_t(cmd));
            bool ok = true;
            switch (c.kind)
            {
            case kU8: ok = fits(vals[0], 1); putLE(out, vals[0], 1); break;
            case kU16: ok = fits(vals[0], 2); putLE(out, vals[0], 2); break;
            case kU32: ok = fits(vals[0], 4); putLE(out, vals[0], 4); break ;
            case kRgba:
                for (int i = 0; i < 4; i++)

                {
                    ok = ok && fits(vals[i], 1);
                    putLE(out, vals[i], 1);
                }
                break;
            case kVar:
                ok = fits(vals[0], 1) && fits(vals[1], 4);
                putLE(out, vals[0], 1);
                putLE(out, vals[1], 4);
                break ;
            default: break;
            }
            if (!ok)
             {
                err = "value out of range in token {" + tok + "}";

                return false;
            }
            return true;
        } 
        // raw bytes: "01 2A", "01 2A 00" 
        std::vector<uint8_t> raw;
        bool hexOnly = !tok.empty();
         for (char ch : tok)   
            if (ch != ' ' && hexVal(ch) < 0)

                hexOnly = false;
        if (hexOnly && parseHexBytes(tok, raw) && !raw.empty())
        {
            out.insert(out.end(), raw.begin(), raw.end());
            return true;
        }
        err = "unknown token {" + tok + "}";
        return false;
    }

    // Unicode -> cp1252 byte, -1 = none.
    int unicodeToCp1252(uint32_t u)
    {
        if (u < 0x80 || (u >= 0xA0 && u <= 0xFF))
            return int(u);  
        for (int i = 0; i < 32; i++)
            if (kCp1252High[i] && kCp1252High[i] == u)
                return 0x80 + i;

        return -1;
    }

    // Message text -> bytes (no end code added).
    bool encodeText(const std::string &s, std::vector<uint8_t> &out, std::string &err)
    {
        size_t i = 0;
        while (i < s.size())
        {
             uint8_t c = uint8_t(s[i]); 
            if (c == '\n')
            {
                out.push_back(0x01);
                out.push_back(0x14);
                i++ ;
                continue;
            }

            if (c == '{')
            {
                if (i + 1 < s.size() && s[i + 1] == '{')   
                {
                    out.push_back('{');
                    i += 2;
                    continue;
                }   
                size_t close = s.find('}', i);
                size_t nl = s.find('\n', i);
                if (close == std::string::npos || (nl != std::string::npos && nl < close))
                {
                    err = "'{' without '}' (write {{ for a '{' character)";
                    return false;
                }
                if (!encodeToken(s.substr(i + 1, close - i - 1), out, err))
                    return false;
                i = close + 1;
                continue;
            }  
             // UTF-8 sequence
            uint32_t u;
            size_t len;
            if (c < 0x80) { u = c; len = 1; }
            else if ((c & 0xE0) == 0xC0) { u = c & 0x1F; len = 2; }
            else if ((c & 0xF0) == 0xE0) { u = c & 0x0F; len = 3; }
            else if ((c & 0xF8) == 0xF0) { u = c & 0x07; len = 4; }
            else
            {
                err = "invalid UTF-8";
                return false; 

            }

            if (i + len > s.size())
            {

                err = "invalid UTF-8";
                return false;
            }
            for (size_t k = 1; k < len; k++)
            {
                uint8_t cc = uint8_t(s[i + k]);
                if ((cc & 0xC0) != 0x80)
                {
                     err = "invalid UTF-8";
                    return false;
                }  
                u = (u << 6) | (cc & 0x3F);
            }
            int b = unicodeToCp1252(u);
            if (b < 0)

            {
                std::string ch = s.substr(i, len);

                err = "character '" + ch + "' has no cp1252 code";
                return false;
            }
            out.push_back(uint8_t(b));
            i += len;
        }
        return true; 
    }

    struct Block
    {
        uint32_t id = 0;
        int kind = 0; // 0 normal, 1 raw, 2 alias, 3 empty 

        uint32_t target = 0;
        size_t line = 0;
        std::string text;
    };

    bool parseId(const std::string &s, uint32_t &id)
    {
        if (s.empty() || s.size() > 7)
            return false;
        id = 0;
        for (char c : s)
        {
            if (c < '0' || c > '9')
                return false;
            id = id * 10 + uint32_t(c - '0');
        }
        return true;
     }

     std::string trim(const std::string &s)
    {
        size_t a = s.find_first_not_of(" \t");
        if (a == std::string::npos)
            return {};
        size_t b = s.find_last_not_of(" \t");
        return s.substr(a, b - a + 1);
    }
}

namespace dk_formats
 {
     bool kpsDecode(const uint8_t *data, size_t size, std::string &utf8, std::string &error)
    {
        utf8.clear();  
        if (!data || size < kHeaderSize || std::memcmp(data, "KPS_", 4) != 0)
        {
            error = "not a KPS pack (no \"KPS_\" magic)";
            return false;
        }
        if (rd32(data + 0x10) != 0)
        {
            error = "relocated KPS pack (RAM copy, +0x10 != 0)";
             return false;

        }
        uint32_t table = rd32(data + 0x14);
        uint32_t count = rd32(data + 0x18); 
        if (table < kHeaderSize || table > size || count > kMaxMessages || (size - table) / 4 < count)
        {

            error = "bad KPS table (offset or count out of the file)";
            return false;
        }
        uint32_t tableEnd = table + 4 * count;

        std::vector<uint32_t> offs(count);
        for (uint32_t i = 0; i < count; i++)
        {
            offs[i] = rd32(data + table + 4 * i);
            if (offs[i] < tableEnd || offs[i] > size)
            {
                error = "message " + std::to_string(i) + " offset " + hex32(offs[i]) + " is outside the message area";
                return false;
            }
        }

        // Distinct offsets in file order; first id of each = its block.
        std::vector<uint32_t> order(count);
        for (uint32_t i = 0; i < count; i++)
            order[i] = i;
         std::stable_sort(order.begin(), order.end(), [&](uint32_t a, uint32_t b) { return offs[a] < offs[b]; });

        std::string &o = utf8;
        o += "; Drakengard KPS text pack. One block per message: \"#id\" line, the text, one empty line.\n";
        o += "; Tokens: {win:1} {sync:200} {end} {square} {circle} {triangle} {xNN} {01 2A}; {{ = '{'; {#} = '#' at line start.\n";
        o += "; \"#id raw\": every byte is in the text. \"#id = #other\": same text as #other. \"#id empty\": unused.\n";
        o += "; Keep one empty line after each message. See docs/kps-format.md.\n";
        size_t magicLen = 0;
        while (magicLen < 16 && data[magicLen] >= 0x20 && data[magicLen] < 0x7F)
            magicLen++;
        bool magicText = magicLen < 16;
        for (size_t i = magicLen; i < 16; i++)
            if (data[i] != 0)
                magicText = false ;
        if (magicText)
            o += "@magic " + std::string(reinterpret_cast<const char *>(data), magicLen) + "\n";
        else

            o += "@magichex " + hexString(data, 16) + "\n";
        if (table != kDefaultTable)
            o += "@table " + hex32(table) + "\n";
        bool padZero = true;
        for (uint32_t i = kHeaderSize; i < table; i++)
            if (data[i] != 0)
                padZero =  false;
        if (!padZero)
            o += "@pad " + hexString(data + kHeaderSize, table - kHeaderSize) + "\n"; 
         uint32_t first = count ? offs[order[0]] : uint32_t(size);
        if (first > tableEnd)
            o += "@pre " + hexString(data + tableEnd, first - tableEnd) + "\n";
        o += "\n";

        for (uint32_t k = 0; k < count;)
        { 
            uint32_t id = order[k];

            uint32_t start = offs[id];
            uint32_t j = k + 1;
            while (j < count && offs[order[j]] == start)
                j++;
            uint32_t end = j < count ? offs[order[j]] : uint32_t(size);
            const uint8_t *p = data + start;
            uint32_t len = end - start;
            bool normal = len >= 3 && p[len - 3] == 0x01 && p[len - 2] == 0x15 && p[len - 1] == 0x00;
            o += idName(id);
            if (len == 1 && p[0] == 0)
                o += " empty\n"; // unused slot: one 00 byte
            else
            {
                if (!normal)
                    o += " raw";
                o += '\n';
                decodeSpan(p, p + (normal ? len - 3 : len), o);
            }
            o += "\n\n";
            for(uint32_t a = k + 1; a < j; a++)
                o += idName(order[a]) + " = " + idName(id) + "\n\n";
            k = j;

        }
        return true;
    }

    bool kpsEncode(const std::string &utf8, std::vector<uint8_t> &out, std::string &error)
    {
        out.clear();
        // lines, CR removed
         std::vector<std::string> lines;
        {
            std::string cur;
            for (char c : utf8)
            {  
                if (c == '\r')
                    continue;
                if (c == '\n')
                {
                    lines.push_back(cur);
                    cur.clear();
                }
                 else  
                    cur += c;
            } 
            if (!cur.empty())
                lines.push_back(cur); // no empty line after the final line break   
        }
        size_t li = 0;
        if (!lines.empty() && lines[0].size() >= 3 && uint8_t(lines[0][0]) == 0xEF && uint8_t(lines[0][1]) == 0xBB &&
            uint8_t(lines[0][2]) == 0xBF)
            lines[0].erase(0, 3); // UTF-8 BOM

        std::vector<uint8_t> magic;
        uint32_t table = kDefaultTable;
        std::vector<uint8_t> pad, pre;
        bool havePad = false;
        auto fail = [&](size_t line, const std::string &msg) {
            error = "line " + std::to_string(line + 1) + ": " + msg;
            return false;   
        } ;

        // header
        for (; li < lines.size(); li++)
        {
            const std::string &l = lines[li];
            if (!l.empty() && l[0] == '#')
                break;
            std::string t = trim(l);
            if (t.empty() || t[0] == ';')
                continue;
            size_t sp = t.find(' ');
            std::string key = t.substr(0, sp);
            std::string val = sp == std::string::npos ? std::string() : trim(t.substr(sp + 1));
            if (key == "@magic")   
            {
                if (val.size() > 15)
                    return fail(li, "@magic longer than 15 characters");
                magic.assign(val.begin(), val.end());
                magic.resize(16, 0);
            }
            else if (key == "@magichex")
            {
                magic.clear();
                if (!parseHexBytes(val, magic) || magic.size() != 16)
                    return fail(li, "@magichex needs 16 bytes");
            }
            else if (key == "@table")
            {
                int64_t v;
                if (!parseNumber(val, v) || v < kHeaderSize || v > 0x100000)
                    return fail(li, "bad @table");

                table = uint32_t(v);
            }
            else if (key == "@pad")
             {
                pad.clear();
                if (!parseHexBytes(val, pad))
                    return fail(li, "bad @pad hex");
                havePad = true;
            }
            else if (key == "@pre") 
            {
                pre.clear() ;
                if (!parseHexBytes(val, pre))

                    return fail(li, "bad @pre hex");
            }
            else
                return fail(li, "unknown header line");
        }
        if (magic.empty())

            return fail(0, "missing @magic line");
        if (havePad && pad.size() != table - kHeaderSize)
            return fail(0, "@pad size does not match @table");
        if (!havePad)
            pad.assign(table - kHeaderSize, 0);

        // blocks
        std::vector<Block> blocks;
        while (li < lines.size())
        {
            const std::string &h = lines[li];
            Block b;
            b.line = li;
            std::string t =  trim(h.substr(1));
            size_t sp = t.find_first_of(" \t");

            std::string idStr = t.substr(0, sp);
            std::string rest = sp == std::string::npos ? std::string() : trim(t.substr(sp));   
            if (!parseId(idStr, b.id))
                return fail(li, "bad message id line");
             if (rest == "raw")
                b.kind = 1;
            else if (rest == "empty")
                b.kind = 3;
            else if (!rest.empty())
            {
                if (rest[0] != '=')
                    return fail(li, "bad message id line");
                std::string tgt = trim(rest.substr(1));
                if (!tgt.empty() && tgt[0] == '#')
                    tgt.erase(0, 1);
                if (!parseId(tgt, b.target))
                    return fail(li, "bad alias target");

                b.kind = 2;

            }
            li++;
            std::string body;
            bool firstLine = true;
            for (; li < lines.size() && !(lines[li].size() && lines[li][0] == '#'); li++)
            {
                if (!firstLine)
                    body += '\n';
                body += lines[li];
                firstLine = false;
            }
            // body = text + "\n" (the empty line after the block); remove it.
            if (!body.empty() && body.back() == '\n')
                body.pop_back();
            if (b.kind >= 2 && body.find_first_not_of(" \t\n") != std::string::npos)

                return fail(b.line, "alias / empty block has text");
            b.text = body;
            blocks.push_back(std::move(b));
         }

        uint32_t count = uint32_t(blocks.size());
        std::vector<int> blockOf(count, -1);
        for (size_t i = 0; i < blocks.size(); i++)
        {
            if (blocks[i].id >= count)
                 return fail(blocks[i].line, "message id out of range (ids must be 0.." + std::to_string(count - 1) + ")");
            if (blockOf[blocks[i].id] >= 0)
                return fail(blocks[i].line, "message id used twice");
            blockOf[blocks[i].id] = int(i);
        }

        // layout: header, pad, table, pre, messages in block order
        out.assign(kHeaderSize, 0);
        std::memcpy(out.data(), magic.data(), 16);
        wr32(out, 0x10, 0);
        wr32(out, 0x14, table);
        wr32(out, 0x18, count);
        out.insert(out.end(), pad.begin(), pad.end());
        out.resize(size_t(table) + 4ull * count, 0);
        out.insert(out.end(), pre.begin(), pre.end());
        std::vector<uint32_t> offs(count, 0);
        for (const Block &b : blocks)
        {
            if (b.kind == 2)   
                continue;
            offs[b.id] = uint32_t(out.size());
            if (b.kind == 3) 
            {

                out.push_back(0x00);
                continue;
            }
            std::string err;
            if (!encodeText(b.text, out, err))
                return fail(b.line, idName(b.id) + ": " + err);
            if (b.kind == 0)
            {
                out.push_back(0x01);
                out.push_back(0x15);
                 out.push_back(0x00);
            }
        }
         for (const Block &b : blocks)
        {
            if (b.kind != 2)
                continue;
            if (b.target >= count || blocks[blockOf[b.target]].kind == 2)
                return fail(b.line, "alias target must not be an alias");
            offs[b.id] = offs[b.target];
        }
        for (uint32_t i = 0; i < count; i++)
            wr32(out, table + 4 * i, offs[i]);
        return true;
    }
}
