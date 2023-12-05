//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "framework/common/i_json_serializable.h"

namespace framework{
    namespace entity{
        class user:public i_json_serializable{
        public:
            std::string name;
            int         age;

            user(common::cstringr name, int age) : name(name), age(age) {}

            hv::Json to_json() const& override{
                return {
                        {"name",name},
                        {"age",age},
                };
            }
            bool from_json(common::cstringr json_str)& override{
                auto tmp = hv::Json::parse(json_str);
                name = tmp.value("name","");
                age = tmp.value("age",0);
                return true;
            }

        };


    }
}
