//
// Created by ahgoogee on 2023/12/4.
//

#pragma once
#include "hv/HttpService.h"

namespace framework{
    class Router
    {
    public:
        static void Register(hv::HttpService& router);
    };
}


