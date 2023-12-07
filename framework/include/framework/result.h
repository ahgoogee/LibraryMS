//
// Created by ahgoogee on 2023/12/5.
//

#pragma once
#include "string"
#include "framework/common/i_json_serializable.h"
#include "hv/json.hpp"
#include "hv/http_content.h"
#include <type_traits>
#include <utility>
#include "common/logger.h"

namespace framework{

    template<typename DataTy>
    struct result{
    public:
        int code{};
        std::string msg;
        bool is_success{};
        DataTy data;

        result(int code,std::string  msg,bool is_success, const DataTy& data)
        :code(code),msg(std::move(msg)),is_success(is_success),data(data){}

        hv::Json to_json() const&{
            return {
                    {"code",code},
                    {"msg",msg},
                    {"is_success",is_success},
                    {"data",data}
            };
        }

        static result<DataTy> ok(const DataTy& data){
            return result<DataTy>{200,"Success",true,data};
        }
    };






}
