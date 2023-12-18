//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "functional"
#include "hv/HttpServer.h"
#include "hv/HttpService.h"
#include "framework/result.h"
#include "framework/common/runtime_exception.h"

namespace framework::service{
    using namespace common;

    class service{
    private:
        hv::HttpService &m_router;
    public:
        service() = delete;
        explicit service(hv::HttpService &_router): m_router(_router){}

        template<class RTy>
        void Handle(const char *method,const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            m_router.Handle(method, path,[processor](const HttpContextPtr& ctx)->int{
                try{
                    result<RTy> res = processor(ctx);
                    ctx->sendJson(res.to_json());
                }catch(const runtime_exception& e){
                    result<void> error{e.code,e.msg,e.is_success};
                    ctx->sendJson(error.to_json());
                }catch(const std::exception& e) {
                    result<void> error{40000,fmt::format("未知错误:{}",e.what()),false};
                    ctx->sendJson(error.to_json());
                }

                //释放local_map
                common::local_map::release();

                return 0;
            });
        }

        template<class RTy>
        void GET(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            Handle("GET",path,std::move(processor));
        }

        template<class RTy>
        void POST(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            Handle("POST",path,std::move(processor));
        }

        template<class RTy>
        void PUT(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            Handle("PUT",path,std::move(processor));
        }

        template<class RTy>
        void Delete(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            Handle("DELETE",path,std::move(processor));
        }

        template<class RTy>
        void HEAD(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            Handle("HEAD",path,std::move(processor));
        }

    };







}





