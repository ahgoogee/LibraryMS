//
// Created by ahgoogee on 2023/12/19.
//

#pragma once
#include "framework/application.h"
#include "framework/common/access_assert.h"
#include "framework/common/runtime_exception.h"
#include "framework/service/service.h"
#include "framework/mapper/mapper.h"
#include "framework/mapper/type_mapper.h"


namespace framework::service{
    using namespace entity;

    class type_service{
    public:
        static void register_service(hv::HttpService &_router,framework::Application& app){
            service serv(_router);

            ::common::logger_ptr log = app.log;
            std::shared_ptr<soci::session> sql = app.sql;

            serv.POST<db_bigint>("/add_type",[sql,log](const HttpContextPtr &ctx){
                type_ro t;
                ctx->json().get_to(t);

                db_bigint id = mapper::type_mapper::add_type(t,sql,log);
                return result<db_bigint>::ok(id);
            });

            serv.POST<std::vector<book_type>>("/list_type_by_id_list",[sql,log](const HttpContextPtr &ctx){
                std::vector<db_bigint> id_list;
                auto j = ctx->json();
                j.at("id_list").get_to(id_list);

                std::vector<book_type> vec = mapper::mapper::list_entity_by_id_list<book_type>(id_list,sql,log);
                return result<std::vector<book_type>>::ok(vec);

            });


            serv.GET<std::vector<book_type>>("/list_type", [sql,log](const HttpContextPtr &ctx){
                std::vector<book_type> vec = framework:: mapper::mapper::list_all_entity<book_type>(sql,log);
                return result<std::vector<book_type>>::ok(vec);
            });

            serv.GET<book_type>("/get_type_by_id", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                book_type t = framework::mapper::mapper::get_entity_by_id<book_type>(id,sql,log);
                return result<book_type>::ok(t);
            });

            serv.GET<bool>("/delete_type_by_id", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                size_t num = framework::mapper::mapper::delete_entity_by_id<book_type>(id,sql,log);
                return result<bool>::ok(num);
            });

            serv.POST<bool>("/update_type_by_id", [sql,log](const HttpContextPtr &ctx){
                book_type u;
                ctx->json().get_to(u);
                size_t num = mapper::type_mapper::update_type_by_id(u,sql,log);
                return result<bool>::ok(num);
            });

            serv.POST<std::vector<book_type>>("/list_type_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                std::vector<book_type> res = framework::mapper::mapper::list_entity_by_page<book_type>(request,sql,log);
                return result<std::vector<book_type>>::ok(res);
            });
            serv.POST<size_t>("/count_type_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                size_t res = framework::mapper::mapper::count_entity_by_page<book_type>(request,sql,log);
                return result<size_t>::ok(res);
            });

            serv.GET<std::vector<book_type>>("/list_type_by_search",[sql,log](const HttpContextPtr &ctx){
                //if(ctx->param("level").empty()) throw runtime_exception{403,"level错误"};
                //if(ctx->param("name").empty()) throw runtime_exception{403,"name错误"};

                db_int level = stoi(ctx->param("level").empty()?"-1":ctx->param("level"));
                std::string name = ctx->param("name");

                std::vector<book_type> res = mapper::type_mapper::list_type_by_search(level,name,sql,log);
                return result<std::vector<book_type>>::ok(res);
            });
        }


    };




}