//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/router.h"
#include "hv/hasync.h"
#include "spdlog/spdlog.h"

void framework::Router::Register(hv::HttpService &router) {
    router.POST("/echo", [](const HttpContextPtr& ctx) {
        spdlog::info("ip:{}",ctx->ip());
        spdlog::info("port:{}",ctx->port());
        spdlog::info("method:{}",http_method_str(ctx->method()));
        spdlog::info("url:{}",ctx->url());
        spdlog::info("host:{}",ctx->host());
        spdlog::info("json:{}",to_string(ctx->json()));

        hv::async([ctx](){
            return ctx->send(ctx->body(), ctx->type());
        });
        return 0;
    });



}