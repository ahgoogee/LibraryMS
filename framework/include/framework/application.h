//
// Created by ahgoogee on 2023/12/4.
//

#pragma once

#include "hv/HttpService.h"
#include "hv/HttpServer.h"

namespace framework{
    class Application{
    private:
        hv::HttpServer  m_http_server;
        hv::HttpService m_http_service;
    public:
        void start();
    };

}


