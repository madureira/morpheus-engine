#pragma once

#include <string>
#include <algorithm>

namespace Morpheus {

    class StringUtil final
    {
    public:
        static inline std::string ToLowerCase(std::string str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
            return str;
        }

        static inline std::string ToUpperCase(std::string str)
        {
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
            return str;
        }
    };

}
