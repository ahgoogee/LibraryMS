//
// Created by ahgoogee on 2023/12/4.
//

#pragma once

#include "hv/HttpService.h"
#include "common/logger.h"
#include "application.h"

namespace framework{

    /**
     * 路由注册类
     * */
    class Router
    {
    public:
        /**
         * 为hv::HttpService注入服务
         * @param router 服务表
         * @param log 使用的日志对象
         * */
        static void Register(hv::HttpService &router, framework::Application &app);
    };
}


