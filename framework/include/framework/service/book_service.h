//
// Created by ahgoogee on 2023/12/19.
//

#pragma once
#include "framework/application.h"
#include "framework/common/access_assert.h"
#include "framework/common/runtime_exception.h"
#include "framework/service/service.h"
#include "framework/mapper/mapper.h"
#include "framework/mapper/book_mapper.h"


namespace framework::service{
    using namespace entity;

    class book_service{
    public:
        static void register_service(hv::HttpService &_router,framework::Application& app){
            service serv(_router);

            ::common::logger_ptr log = app.log;
            std::shared_ptr<soci::session> sql = app.sql;

            serv.POST<db_bigint>("/add_book",[sql,log](const HttpContextPtr &ctx){
                book_ro t;
                ctx->json().get_to(t);

                db_bigint id = mapper::book_mapper::add_book(t,sql,log);
                return result<db_bigint>::ok(id);
            });

            serv.GET<std::vector<book>>("/list_book", [sql,log](const HttpContextPtr &ctx){
                std::vector<book> vec = framework::mapper::mapper::list_all_entity<book>(sql,log);
                return result<std::vector<book>>::ok(vec);
            });

            serv.GET<book>("/get_book_by_id", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                book t = framework::mapper::mapper::get_entity_by_id<book>(id,sql,log);
                return result<book>::ok(t);
            });

            serv.GET<bool>("/delete_book_by_id", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                size_t num = framework::mapper::mapper::delete_entity_by_id<book>(id,sql,log);
                return result<bool>::ok(num);
            });

            serv.POST<bool>("/update_book_by_id", [sql,log](const HttpContextPtr &ctx){
                book u;
                ctx->json().get_to(u);
                size_t num = mapper::book_mapper::update_book_by_id(u,sql,log);
                return result<bool>::ok(num);
            });

            serv.POST<std::vector<book>>("/list_book_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                std::vector<book> res = framework::mapper::mapper::list_entity_by_page<book>(request,sql,log);
                return result<std::vector<book>>::ok(res);
            });
            serv.POST<size_t>("/count_book_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                size_t res = framework::mapper::mapper::count_entity_by_page<book>(request,sql,log);
                return result<size_t>::ok(res);
            });

            serv.GET<std::vector<book>>("/list_book_by_search",[sql,log](const HttpContextPtr &ctx){
                //if(ctx->param("level").empty()) throw runtime_exception{403,"level错误"};
                //if(ctx->param("name").empty()) throw runtime_exception{403,"name错误"};

                std::string name = ctx->param("name");

                std::vector<book> res = mapper::book_mapper::list_book_by_search(name,sql,log);
                return result<std::vector<book>>::ok(res);
            });

            serv.GET<bool>("/update_book_borrow_state_by_id",[sql,log](const HttpContextPtr &ctx){
                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                std::string state = ctx->param("borrow_state");

                size_t num = mapper::book_mapper::update_book_borrow_state_by_id(id,state,sql,log);
                return result<bool>::ok(num);
            });

        }
    };

}