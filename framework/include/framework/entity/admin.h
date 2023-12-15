//
// Created by ahgoogee on 2023/12/14.
//

#pragma once

#include <utility>
#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"
#include "framework/entity/entity.h"


namespace framework::entity{
    struct admin{
    public:
    TABLE(admin);
    PK(id);
    COLUMN(id,db_bigint);
    COLUMN(username,db_varchar);
        //COLUMN(password,db_varchar);
    COLUMN(creation_time,db_datetime);
        //COLUMN(update_time,db_datetime);

        admin() = default;


        friend void to_json(hv::Json& j, const admin& p) {
            j = hv::Json{
                    {admin::id_name,p.id},
                    {admin::username_name, p.username},
                    //{user::password_name, p.password},
                    {admin::creation_time_name,to_string(p.creation_time)},
                    //{user::update_time_name,p.update_time}
            };
        }
        friend void from_json(const hv::Json& j, admin& p) {
            j.at(admin::id_name).get_to(p.id);
            j.at(admin::username_name).get_to(p.username);
            //j.at("password").get_to(p.password);
            from_string(p.creation_time,j.at(admin::creation_time_name).get<std::string>());
            //j.at("update_time").get_to(p.update_time);

        }
    };

    struct admin_ro{
        db_varchar username;
    };
}
namespace soci{
    using namespace framework::entity;
    template<>
    struct type_conversion<framework::entity::admin>{
        typedef values base_type;

        static void from_base(values const &v, indicator const &ind, framework::entity::admin &p) {
            if (ind == i_ok) {
                p.id = v.get<db_bigint>(admin::id_name);
                p.username = v.get<db_varchar>(admin::username_name);
                //p.password = v.get<db_varchar>("password");
                p.creation_time = v.get<db_datetime>(admin::creation_time_name);
                //p.update_time = v.get<db_datetime>("update_time");
            }
        }

        static void to_base(framework::entity::admin const &p, values &v, indicator &ind) {
            v.set(admin::id_name, p.id);
            v.set(admin::username_name, p.username);
            //v.set("password",p.password);
            v.set(admin::creation_time_name, p.creation_time);
            //v.set("update_time", p.update_time);
            ind = i_ok;
        }
    };



}