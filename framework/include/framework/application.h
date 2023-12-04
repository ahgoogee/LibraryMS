//
// Created by ahgoogee on 2023/12/4.
//

#pragma once

#include "hv/HttpService.h"
#include "hv/HttpServer.h"

namespace framework{
    class Application{
    public:
        void run(uint16_t port = 8080);
    private:
        hv::HttpServer  m_http_server;
        hv::HttpService m_http_service;
    };

}


