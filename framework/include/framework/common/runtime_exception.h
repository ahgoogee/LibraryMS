//
// Created by ahgoogee on 2023/12/8.
//

#pragma once

#include <exception>
#include "framework/result.h"

namespace common{
    class runtime_exception:public std::exception{
    public:
        int code;
        const char *msg;
        bool is_success;
        runtime_exception(int code, const char* msg,bool is_success = false)
        : code(code),msg(msg),is_success(is_success)
        {}
    };
}
