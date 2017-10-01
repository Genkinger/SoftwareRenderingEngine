//
// Created by genkinger on 9/22/17.
//

#include <iostream>
#include "StringUtils.h"

std::vector<std::string> Utils::StringUtils::Split(std::string input, std::string delimiter, bool compress) {

    std::vector<std::string> result;

    auto pos = input.find(delimiter);
    unsigned long prev = 0;
    while(pos != std::string::npos){
        result.push_back(input.substr(prev,pos-prev));
        prev = pos + delimiter.length();
        pos = input.find(delimiter,pos+1);
    }
    result.push_back(input.substr(prev));


    if(compress){
        for (auto& str : result) {
            std::remove_if(str.begin(),str.end(),isspace);
        }
    }

    return result;
}

std::string Utils::StringUtils::ToLower(std::string input) {
    std::string result = "";

    for (int i = 0; i < input.length(); ++i) {
        result += tolower(input[i]);
    }

    return result;
}

std::string Utils::StringUtils::ToUpper(std::string input) {
    std::string result = "";

    for (int i = 0; i < input.length(); ++i) {
        result += toupper(input[i]);
    }

    return result;
}









