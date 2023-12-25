//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/application.h"
#include "framework/router.h"
#include "exception"

namespace framework{
    void Application::run(uint16_t port) {
        Router::Register(m_http_service, *this);

        m_http_server.registerHttpService(&m_http_service);
        m_http_server.port = {port};
        try{
            m_http_server.run();
        }
        catch (const std::exception& e){
            log->error(e.what());
        }
    }


}

