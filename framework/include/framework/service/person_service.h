//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "service.h"
#include "framework/entity/user.h"
#include "hv/HttpService.h"
#include "framework/application.h"
#include "soci/rowset.h"
#include "fmt/format.h"


namespace framework::service{
    using namespace entity;

    class person_service{
    public:
        static void register_service(hv::HttpService &_router,framework::Application& app){
            service serv(_router);

            common::logger_ptr log = app.log;
            std::shared_ptr<soci::session> sql = app.sql;

            serv.GET<std::vector<person>>("/list_person", [sql,log](const HttpContextPtr &ctx){
                std::vector<person> vec;

//                *sql << fmt::format("select * from {}",person::table),soci::into(vec);
                return result<std::vector<person>>::ok(vec);
            });





        }
    };




}




