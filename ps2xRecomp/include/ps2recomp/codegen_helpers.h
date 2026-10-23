#ifndef PS2RECOMP_CODEGEN_HELPERS_H
#define PS2RECOMP_CODEGEN_HELPERS_H

#include <cctype>
#include <cmath>
#include <cstdint>
#include <string>
#include <string_view>
#include <fmt/format.h>

namespace ps2recomp::codegen
{
    inline std::string formatFloatLiteral(float value)
    {
        if (!std::isfinite(value))
        {
            return (value < 0.0f) ? "-INFINITY" : "INFINITY";
        }

        std::string literal = fmt::format("{:.9g}", value);
        if (literal.find_first_of(".eE") == std::string::npos)
        {
            literal += ".0";
        }
        literal += 'f';
        return literal;
    }

    inline std::string vuMaskExpr(uint8_t dest_mask)
    {
        return fmt::format("_mm_castsi128_ps(_mm_set_epi32({}, {}, {}, {}))",
                           (dest_mask & 0x1) ? -1 : 0,
                           (dest_mask & 0x2) ? -1 : 0,
                           (dest_mask & 0x4) ? -1 : 0,
                           (dest_mask & 0x8) ? -1 : 0);
    }

    inline bool codeNeedsGuestPc(std::string_view code)
    {
        if (code.find("runtime") != std::string_view::npos ||
            code.find("ctx->pc") != std::string_view::npos ||
            code.find("throw") != std::string_view::npos)
        {
            return true;
        }

        for (std::string_view prefix : {std::string_view("READ"), std::string_view("WRITE")})
        {
            size_t pos = code.find(prefix);
            while (pos != std::string_view::npos)
            {
                const bool wordStart = pos == 0 ||
                                       !(std::isalnum(static_cast<unsigned char>(code[pos - 1])) || code[pos - 1] == '_');
                size_t end = pos + prefix.size();
                while (end < code.size() && std::isdigit(static_cast<unsigned char>(code[end])))
                {
                    ++end;
                }
                if (wordStart && end > pos + prefix.size() && end < code.size() && code[end] == '(')
                {
                    return true;
                }
                pos = code.find(prefix, pos + 1);
            }
        }
        return false;
    }
}

#endif // PS2RECOMP_CODEGEN_HELPERS_H
