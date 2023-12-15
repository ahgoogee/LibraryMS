//
// Created by ahgoogee on 2023/12/15.
//

#pragma once
#include "common/utils/local_map.h"
#include "framework/entity/token.h"
#include "common/utils/cstringr.h"
#include "runtime_exception.h"

namespace common{
    static void access_assert(cstringr usertype){
        auto local = local_map::local();
        std::string cache_usertype = local_map::local().at("usertype");
        if(cache_usertype != usertype){
            throw runtime_exception(20002,"拒绝访问");
        }
    }


}
