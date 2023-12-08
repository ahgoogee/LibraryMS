//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "vector"
#include "framework/service/service.h"
#include "framework/entity/user.h"
#include "framework/application.h"
#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"
#include "framework/mapper/user_mapper.h"
#include "framework/common/runtime_exception.h"

namespace framework::service{
    using namespace entity;

    class person_service{
    public:
        static void register_service(hv::HttpService &_router,framework::Application& app){
            service serv(_router);

            common::logger_ptr log = app.log;
            std::shared_ptr<soci::session> sql = app.sql;

            serv.GET<std::vector<user>>("/list_user", [sql,log](const HttpContextPtr &ctx){
                std::vector<user> vec = mapper::user_mapper::list_all_user(sql,log);
                return result<std::vector<user>>::ok(vec);
            });


            serv.GET<user>("/get_user_by_id", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("id") == "") throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                user u = mapper::user_mapper::get_user_by_id(id,sql,log);
                return result<user>::ok(u);
            });

            serv.GET<bool>("/delete_user_by_id", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("id") == "") throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                size_t num = mapper::user_mapper::delete_user_by_id(id,sql,log);
                return result<bool>::ok(num);
            });

            serv.POST<bool>("/update_user_by_id", [sql,log](const HttpContextPtr &ctx){
                user u;
                ctx->json().get_to(u);
                size_t num = mapper::user_mapper::update_user_by_id(u,sql,log);
                return result<bool>::ok(num);
            });

        }
    };




}




