//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include <utility>
#include "framework/common/i_json_serializable.h"
#include "soci/mysql/soci-mysql.h"
#include "soci/values.h"


namespace framework::entity{
    struct person{
    public:
        TABLE(person);
        PK(id);
        uint64_t id;
        std::string first_name;
        std::string last_name;

        person() = default;

        person(common::cstringr firstName, common::cstringr lastName)
        : first_name(firstName),last_name(lastName) {}

        person(uint64_t id, common::cstringr firstName, common::cstringr lastName)
        : id(id), first_name(firstName),last_name(lastName) {}

        friend void to_json(hv::Json& j, const person& p) {
            j = {
                    {"id",p.id},
                    {"first_name", p.first_name},
                    {"last_name", p.last_name}
            };
        }

        friend void from_json(const hv::Json& j, person& p) {
            j.at("id").get_to(p.id);
            j.at("first_name").get_to(p.first_name);
            j.at("last_name").get_to(p.last_name);
        }
    };
}
namespace soci{
    template <>
    struct type_conversion<framework::entity::person> {
        typedef values base_type;

        static void from_base(values const &v, indicator const &ind, framework::entity::person &p) {
            if (ind == i_ok) {
                p.id = v.get<int64_t>("id");
                p.first_name = v.get<std::string>("first_name");
                p.last_name = v.get<std::string>("last_name");
            }
        }

        static void to_base(framework::entity::person const &p, values &v, indicator &ind) {
            v.set("id", p.id);
            v.set("first_name", p.first_name);
            v.set("last_name", p.last_name);
            ind = i_ok;

        }
    };
}
