//
// Created by ahgoogee on 2023/12/4.
//

#include "iostream"
#include "framework/application.h"
#include "framework/router.h"

namespace framework{
    void Application::run(uint16_t port) {
        Router::Register(m_http_service);
        m_http_server.registerHttpService(&m_http_service);
        m_http_server.port = {port};

        m_http_server.run();
    }


}

