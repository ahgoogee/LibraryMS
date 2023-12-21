//
// Created by ahgoogee on 2023/12/19.
//

#pragma once
#include "framework/application.h"
#include "framework/common/access_assert.h"
#include "framework/common/runtime_exception.h"
#include "framework/service/service.h"
#include "framework/mapper/mapper.h"
#include "framework/mapper/record_mapper.h"


namespace framework::service {
    using namespace entity;

    class record_service{
    public:
        static void register_service(hv::HttpService &_router,framework::Application& app){
            service serv(_router);

            ::common::logger_ptr log = app.log;
            std::shared_ptr<soci::session> sql = app.sql;

            serv.GET<db_bigint>("/borrow_to",[sql,log](const HttpContextPtr &ctx){
                if(local_map::local()["user_id"].empty()) throw runtime_exception{403,"user_id错误"};
                if(ctx->param("book_id").empty()) throw runtime_exception{403,"book_id错误"};

                int uid = stoi(local_map::local()["user_id"]);
                int bid = stoi(ctx->param("book_id"));

                auto id = mapper::record_mapper::borrow_to(uid,bid,sql,log);
                return result<db_bigint>::ok(id);
            });

            serv.GET<bool>("/give_back",[sql,log](const HttpContextPtr &ctx){
                if(ctx->param("record_id").empty()) throw runtime_exception{403,"record_id错误"};

                int rid = stoi(ctx->param("record_id"));

                auto num = mapper::record_mapper::give_back(rid,sql,log);
                return result<bool>::ok(num);
            });

            serv.POST<std::vector<record>>("/list_record_by_id_list",[sql,log](const HttpContextPtr &ctx){
                std::vector<db_bigint> id_list;
                auto j = ctx->json();
                j.at("id_list").get_to(id_list);

                std::vector<record> vec = mapper::mapper::list_entity_by_id_list<record>(id_list,sql,log);
                return result<std::vector<record>>::ok(vec);

            });

            serv.GET<std::vector<record>>("/list_record", [sql,log](const HttpContextPtr &ctx){
                std::vector<record> vec = framework::mapper::mapper::list_all_entity<record>(sql,log);
                return result<std::vector<record>>::ok(vec);
            });

            serv.GET<record>("/get_record_by_id", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                auto t = framework::mapper::mapper::get_entity_by_id<record>(id,sql,log);
                return result<record>::ok(t);
            });


            serv.POST<std::vector<record>>("/list_record_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                std::vector<record> res = framework::mapper::mapper::list_entity_by_page<record>(request,sql,log);
                return result<std::vector<record>>::ok(res);
            });
            serv.POST<size_t>("/count_record_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                size_t res = framework::mapper::mapper::count_entity_by_page<record>(request,sql,log);
                return result<size_t>::ok(res);
            });









        }
    };

}
