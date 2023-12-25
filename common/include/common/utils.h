//
// Created by ahgoogee on 2023/12/7.
//

#pragma once


#include "common/utils/constexpr_string.h"
#include "common/utils/cstringr.h"
#include "common/utils/pipe_operator.h"
#include "common/utils/local_map.h"

namespace common{
    static std::string join(common::cstringr separator,std::vector<std::string> list){
        if(list.empty()) return "";

        std::ostringstream oss;
        oss << list[0];
        for (size_t i = 1; i < list.size(); ++i) {
            oss << separator << list[i];
        }

        return oss.str();
    }

}

