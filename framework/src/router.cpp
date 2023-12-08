//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/router.h"
#include "hv/hasync.h"
#include "framework/service/person_service.h"
#include "framework/application.h"

using namespace common;

void framework::Router::Register(hv::HttpService &router, Application &app) {
    common::logger_ptr log = app.log;
    type::dbsession_ptr sql = app.sql;

    /**
     *  /echo
     *  原样返回http请求body
     * */
    router.POST("/echo", [](const HttpContextPtr& ctx) {
        hv::async([ctx](){
            return ctx->send(ctx->body(), ctx->type());
        });
        return 0;
    });


    service::person_service::register_service(router,app);


    router.middleware.emplace_back([log](const HttpContextPtr & ctx)->int{
        log->info("/-------------------------\\");
        log->info("source :{}:{}",ctx->ip(),ctx->port());
        log->info("method :{}",http_method_str(ctx->method()));
        log->info("url    :{}",ctx->url());
        std::string params;
        std::for_each(ctx->params().begin(), ctx->params().end(),[&params](const auto&val){
            params += fmt::format("{}={};",val.first,val.second);
        });
        log->info("params :{}",params);
        log->info("body   :{}",to_string(ctx->json()));
        log->info("\\________________________/");

        return HTTP_STATUS_NEXT;
    });


}