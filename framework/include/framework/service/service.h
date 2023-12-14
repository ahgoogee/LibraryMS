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
    class service{
    private:
        hv::HttpService &m_router;
    public:
        service() = delete;
        explicit service(hv::HttpService &_router): m_router(_router){}

        template<class RTy>
        void POST(const char *path, std::function<result<RTy>(const HttpContextPtr&)> processor){
            m_router.POST(path,[processor](const HttpContextPtr& ctx)->int{
                try{
                    result<RTy> res = processor(ctx);
                    ctx->sendJson(res.to_json());
                }catch(const runtime_exception& e){
                    result<void> error{e.code,e.msg,e.is_success};
                    ctx->sendJson(error.to_json());
                } catch (const std::exception& e) {
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
            m_router.GET(path,[processor](const HttpContextPtr& ctx)->int{
                try{
                    result<RTy> res = processor(ctx);
                    ctx->sendJson(res.to_json());
                }catch(const runtime_exception& e){
                    result<void> error{e.code,e.msg,e.is_success};
                    ctx->sendJson(error.to_json());
                } catch (const std::exception& e) {
                    result<void> error{40000,fmt::format("未知错误:{}",e.what()),false};
                    ctx->sendJson(error.to_json());
                }

                //释放local_map
                common::local_map::release();

                return 0;
            });
        }

    };







}





