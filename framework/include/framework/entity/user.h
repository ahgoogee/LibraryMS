//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include <utility>
#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"
#include "framework/entity/entity.h"


namespace framework::entity{
    struct user{
    public:
        TABLE(user);
        PK(id);
        COLUMN(id,db_bigint);
        COLUMN(first_name,db_varchar);
        COLUMN(last_name,db_varchar);

        user() = default;

        user(const db_varchar &mFirstName, const db_varchar &mLastName)
        : m_first_name(mFirstName),m_last_name(mLastName)
        {}

        user(db_bigint mId, const db_varchar &mFirstName, const db_varchar &mLastName)
        : m_id(mId),m_first_name(mFirstName),m_last_name(mLastName)
        {}

        friend void to_json(hv::Json& j, const user& p) {
            j = {
                    {"id",p.get_id()},
                    {"first_name", p.get_first_name()},
                    {"last_name", p.get_last_name()}
            };
        }
        friend void from_json(const hv::Json& j, user& p) {
            j.at("id").get_to(p.m_id);
            j.at("first_name").get_to(p.m_first_name);
            j.at("last_name").get_to(p.m_last_name);
        }
    };
}
namespace soci{
    template<>
    struct type_conversion<framework::entity::user>{
        typedef values base_type;

        static void from_base(values const &v, indicator const &ind, framework::entity::user &p) {
            if (ind == i_ok) {
                p.set_id(v.get<int64_t>("id"));
                p.set_first_name(v.get<std::string>("first_name"));
                p.set_last_name(v.get<std::string>("last_name"));
            }
        }

        static void to_base(framework::entity::user const &p, values &v, indicator &ind) {
            v.set("id", p.get_id());
            v.set("first_name", p.get_first_name());
            v.set("last_name", p.get_last_name());
            ind = i_ok;
        }
    };



}