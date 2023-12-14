//
// Created by ahgoogee on 2023/12/14.
//

#pragma once
#include "framework/common/types.h"
#include "hv/http_content.h"

namespace framework::entity{
    struct token{
        type::db_bigint user_id;
        type::db_varchar username;
        std::string usertype;

    public:
        token() = default;
        token(db_bigint userId, const db_varchar &username, const std::string &usertype)
        : user_id(userId),
        username(username),
        usertype(usertype)
        {}

        static void cache(std::map<std::string,std::string>& position,const token& t){
            position["user_id"] = fmt::format("{}",t.user_id);
            position["username"] = t.username;
            position["usertype"] = t.usertype;
        }

        friend void to_json(hv::Json& j, const token& t) {
            j = hv::Json{
                    {"user_id",t.user_id},
                    {"username",t.username},
                    {"usertype",t.usertype}
            };
        }
        friend void from_json(const hv::Json& j, token& t) {
            j.at("user_id").get_to(t.user_id);
            j.at("username").get_to(t.username);
            j.at("usertype").get_to(t.usertype);
        }
    };
}
