//
// Created by genkinger on 9/22/17.
//

#ifndef ENGINE_STRINGUTILS_H
#define ENGINE_STRINGUTILS_H

#include <string>
#include <vector>
#include <algorithm>

namespace Utils {

    class StringUtils {
    public:
        static std::vector<std::string> Split(std::string input, std::string delimiter, bool compress);

        static std::string ToLower(std::string input);
        static std::string ToUpper(std::string input);

    };
}

#endif //ENGINE_STRINGUTILS_H
