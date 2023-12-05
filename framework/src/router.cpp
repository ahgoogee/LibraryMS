//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/router.h"
#include "hv/hasync.h"
#include "framework/service/user_service.h"

using namespace common;

void framework::Router::Register(hv::HttpService &router, logger log) {
    /**
     *  /echo
     *  原样返回http请求body
     * */
    router.POST("/echo", [&log](const HttpContextPtr& ctx) {


        hv::async([ctx](){
            return ctx->send(ctx->body(), ctx->type());
        });
        return 0;
    });

    service::user_service::register_service(router);


    router.middleware.emplace_back([&log](const HttpContextPtr & ctx)->int{
        log->info("/-------------------------\\");
        log->info("source :{}:{}",ctx->ip(),ctx->port());
        log->info("method :{}",http_method_str(ctx->method()));
        log->info("url    :{}",ctx->url());
        log->info("body   :{}",to_string(ctx->json()));
        log->info("\\________________________/");

        return HTTP_STATUS_NEXT;
    });


}