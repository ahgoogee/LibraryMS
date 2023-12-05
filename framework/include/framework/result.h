//
// Created by ahgoogee on 2023/12/5.
//

#pragma once
#include "string"
#include "framework/common/i_json_serializable.h"
#include "hv/json.hpp"
#include "hv/http_content.h"
#include <type_traits>
#include "common/logger.h"

namespace framework{

    template<typename DataTy
            ,typename = typename std::enable_if_t<std::is_base_of_v<i_json_serializable, DataTy>>
            >
    struct result:i_json_serializable{
    public:
        int code{};
        std::string msg;
        bool is_success{};
        DataTy data;

        result(int code,common::cstringr msg,bool is_success, const DataTy& data)
        :code(code),msg(msg),is_success(is_success),data(data){}

        hv::Json to_json() const& override{
            return {
                    {"code",code},
                    {"msg",msg},
                    {"is_success",is_success},
                    {"data",data.to_json()}
            };
        }
        bool from_json(common::cstringr json_str)& override{
            assert("理论上一个result不该由后端来反序列化");
            return true;
        }

        static result<DataTy> ok(const DataTy& data){
            return {200,"Success",true,data};
        }
    };






}
