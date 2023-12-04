//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/router.h"

void framework::Router::Register(hv::HttpService &router) {
    router.POST("/echo", [](const HttpContextPtr& ctx) {
        return ctx->send(ctx->body(), ctx->type());
    });



}