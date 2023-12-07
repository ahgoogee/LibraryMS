//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "common/uitls/cstringr.h"
#include "framework/result.h"
#include "functional"
#include "hv/HttpService.h"
#include "framework/entity/entity.h"


namespace framework::service{
    using namespace entity;

    class service{
    private:
        hv::HttpService &m_router;
    public:
        service() = delete;
        explicit service(hv::HttpService &_router): m_router(_router){}

        template<class RTy>
        void POST(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            m_router.POST(path,[processor](const HttpContextPtr& ctx)->int{
                result<RTy> res = processor(ctx);
                ctx->sendJson(res.to_json());
                return 0;
            });
        }

        template<class RTy>
        void GET(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            m_router.GET(path,[processor](const HttpContextPtr& ctx)->int{
                result<RTy> res = processor(ctx);
                ctx->sendJson(res.to_json());
                return 0;
            });
        }

    };







}





