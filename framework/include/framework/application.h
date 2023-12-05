//
// Created by ahgoogee on 2023/12/4.
//

#pragma once

#include <utility>

#include "hv/HttpService.h"
#include "hv/HttpServer.h"
#include "common/logger.h"

namespace framework{
    /**
     * 服务启动类
     * @example:
     * @code
     *      auto app = framework::Application(common::create_logger());
     *      app.run(8080); //阻塞运行
     * @endcode
     *
     * */
    class Application{
    public:
        explicit Application(common::logger _log = common::create_logger()):log(std::move(_log)){}

        void run(uint16_t port = 8080);
    private:
        hv::HttpServer  m_http_server;
        hv::HttpService m_http_service;
        common::logger log;
    };

}


