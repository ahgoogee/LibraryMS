//
// Created by ahgoogee on 2023/12/5.
//

#pragma once
#include "string"
namespace common{
    /**
     * const std::string&的简写
     * */
    using cstringr = const std::string&;
    using cstring = const std::string;
    using stringr = std::string&;
    using stringrr = std::string&&;
}