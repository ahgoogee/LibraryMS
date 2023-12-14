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
#include "framework/entity/token.h"

namespace framework::service{
    using namespace entity;

    class user_service{
    public:
        static void register_service(hv::HttpService &_router,framework::Application& app){
            service serv(_router);

            common::logger_ptr log = app.log;
            std::shared_ptr<soci::session> sql = app.sql;

            serv.POST<std::string>("/login",[sql,log](const HttpContextPtr &ctx){
                std::string username;
                std::string password;
                std::string usertype;
                hv::Json json = ctx->json();
                json.at("username").get_to(username);
                json.at("password").get_to(password);
                json.at("usertype").get_to(usertype);

                std::string token =  mapper::user_mapper::login(username,password,usertype,sql,log);

                return result<std::string>::ok(token);;
            });

            serv.POST<db_bigint>("/add_user", [sql,log](const HttpContextPtr &ctx){
                user u;
                ctx->json().get_to(u);

                db_bigint id = mapper::user_mapper::add_user(u,sql,log);
                return result<db_bigint>::ok(id);
            });

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




