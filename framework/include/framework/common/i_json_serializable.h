//
// Created by ahgoogee on 2023/12/5.
//

#pragma once
#include "string"
#include "common/uitls/cstringr.h"
#include "hv/http_content.h"

namespace framework{
    /**
     * json序列化接口
     * */
    class i_json_serializable{
    public:
        virtual hv::Json to_json() const& = 0;
        virtual bool from_json(common::cstringr)& = 0;
    };
}