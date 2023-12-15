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
#include "framework/common/types.h"

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
        explicit Application(common::cstringr db_string,common::logger_ptr _log = common::create_logger())
        :log(std::move(_log))
        {
            try {
                log->trace("Mysql connect string:\"{}\"",db_string);
                /*NOTE:移除了服务器ssl验证并指定test数据库root用户使用native密码验证通过才链接成功*/
                sql = std::make_shared<soci::session>(soci::mysql, db_string);
            }
            catch (std::exception e){
                log->error("mysql error:{}",e.what());
                exit(-12345);
            }
        }

        void run(uint16_t port = 8080);

        common::logger_ptr log;
        common::type::dbsession_ptr sql;
    private:
        hv::HttpServer  m_http_server;
        hv::HttpService m_http_service;

    };

}


