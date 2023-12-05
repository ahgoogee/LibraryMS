//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "service.h"
#include "framework/entity/user.h"
#include "hv/HttpService.h"

namespace framework{
    namespace service{
        class user_service{
        public:
            static void register_service(hv::HttpService &_router){
                service serv(_router);

                serv.post<user>("/get_user",[](const HttpContextPtr& ctx){
                    return result<user>::ok(user("name",11));
                });





            }
        };




    }



}
