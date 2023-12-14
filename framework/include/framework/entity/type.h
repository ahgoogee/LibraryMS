//
// Created by ahgoogee on 2023/12/14.
//

#pragma once
#include "framework/entity/entity.h"
#include "soci/soci.h"

namespace framework::entity{
    struct type{
    public:
        TABLE(type);
        PK(id);
        COLUMN(id,db_bigint);
        COLUMN(name,db_varchar);
        COLUMN(level,db_int);
        COLUMN(parent_id,db_bigint);
        COLUMN(creation_time,db_datetime);



        friend void to_json(hv::Json& j, const type& t) {
            j = hv::Json{
                    {type::id_name,t.id},
                    {type::name_name, t.name},
                    {type::level_name, t.level},
                    {type::parent_id_name,t.parent_id},
                    {type::creation_time_name,to_string(t.creation_time)  },
            };
        }
        friend void from_json(const hv::Json& j, type& t) {
            j.at(type::id_name).get_to(t.id);
            j.at(type::name_name).get_to(t.name);
            j.at(type::level_name).get_to(t.level);
            j.at(type::parent_id_name).get_to(t.parent_id);
            from_string(t.creation_time,j.at(type::creation_time_name).get<std::string>());
        }
    };
}

namespace soci{
    using namespace framework::entity;
    template<>
    struct type_conversion<type>{
        typedef values base_type;

        static void from_base(values const &v, indicator const &ind, type &t) {
            if (ind == i_ok) {
                t.id = v.get<db_bigint>(type::id_name);
                t.name = v.get<db_varchar>(type::name_name);
                t.level = v.get<db_int>(type::level_name);
                t.parent_id = v.get<db_bigint>(type::parent_id_name);
                t.creation_time = v.get<db_datetime>(type::creation_time_name);
            }
        }

        static void to_base(type const &t, values &v, indicator &ind) {
            v.set(type::id_name,t.id);
            v.set(type::name_name, t.name);
            v.set(type::level_name,t.level);
            v.set(type::parent_id_name,t.parent_id);
            v.set(type::creation_time_name,t.creation_time);

            ind = i_ok;
        }
    };
}