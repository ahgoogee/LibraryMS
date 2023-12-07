//
// Created by ahgoogee on 2023/12/4.
//

#pragma once

#include <utility>

#include "hv/HttpService.h"
#include "hv/HttpServer.h"
#include "common/logger.h"
#include "soci/session.h"
#include "soci/mysql/soci-mysql.h"

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
        explicit Application(common::logger_ptr _log = common::create_logger())
        :log(std::move(_log))
        {
            try {
                sql = std::make_shared<soci::session>(soci::mysql, "host=61.139.65.141 port=10390 dbname=test user=root password=123456");
            }
            catch (std::exception e){
                log->error("mysql error:{}",e.what());
                exit(-12345);
            }
        }

        void run(uint16_t port = 8080);

        common::logger_ptr log;
        std::shared_ptr<soci::session> sql;
    private:
        hv::HttpServer  m_http_server;
        hv::HttpService m_http_service;

    };

}


