//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/router.h"
#include "hv/hasync.h"
#include "framework/service/user_service.h"
#include "framework/service/type_service.h"
#include "framework/application.h"
#include "cppcodec/base64_rfc4648.hpp"
#include "framework/pojo/token.h"
#include "common/utils.h"
#include "framework/service/book_service.h"
#include "framework/service/record_service.h"


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


    service::user_service::register_service(router, app);
    service::type_service::register_service(router, app);
    service::book_service::register_service(router, app);
    service::record_service::register_service(router, app);

    router.AllowCORS();

    router.middleware.emplace_back([log](const HttpContextPtr & ctx)->int{
        /// 接口访问日志打印中间件
        log->info("/-------------------------\\");
        log->info("source :{}:{}",ctx->ip(),ctx->port());
        log->info("method :{}",http_method_str(ctx->method()));
        log->info("url    :{}",ctx->url());
        log->info("path   :{}",ctx->path());
        std::string params;
        std::for_each(ctx->params().begin(), ctx->params().end(),[&params](const auto&val){
            params += fmt::format("{}={};",val.first,val.second);
        });
        log->info("params :{}",params);
        log->info("body   :{}",to_string(ctx->json()));
        log->info("username:{}",local_map::local()["username"]);
        log->info("usertype:{}",local_map::local()["usertype"]);
        log->info("\\________________________/");

        return HTTP_STATUS_NEXT;
    });

    router.middleware.emplace_back([log](const HttpContextPtr & ctx)->int{
        /// token 认证中间件S
        std::vector<std::string> exclude{
                "/login"
        };
        if(std::find(exclude.begin(), exclude.end(),ctx->path()) != exclude.end())
            return HTTP_STATUS_NEXT;
        try{
            std::string token_string = ctx->header("Token");
            using base64 = cppcodec::base64_rfc4648;
            std::vector<unsigned char> decoded = base64::decode(token_string);
            framework::entity::token t;
            std::string token_str = std::string{decoded.begin(), decoded.end()};
            log->info("Token    :{}",token_str);
            hv::Json json;
            std::string errmsg;
            hv::parse_json(token_str.c_str(),json,errmsg);
            json.at(0).get_to(t);

            framework::entity::token::cache(common::local_map::local(),t);
        }
        catch (const std::exception& e){
            log->error("auth error:{}",e.what());
            return HTTP_STATUS_UNAUTHORIZED;
        }
        return HTTP_STATUS_NEXT;
    });





}