//
// Created by ahgoogee on 2023/12/14.
//

#pragma once
#include "framework/entity/entity.h"
#include "soci/soci.h"

namespace framework::entity{
    struct record{
    public:
        TABLE(record);
        PK(id);
        COLUMN(id,db_bigint);
        COLUMN(book_id,db_bigint);
        COLUMN(user_id,db_bigint);
        COLUMN(creation_time,db_datetime);
        COLUMN(stop_time,db_datetime);


        friend void to_json(hv::Json& j, const record& r) {
            j = hv::Json{
                    {"id", r.id},
                    {"book_id", r.book_id},
                    {"user_id", r.user_id},
                    {"creation_time", to_string(r.creation_time)},
                    {"stop_time", to_string(r.stop_time)}
            };
        }

        friend void from_json(const hv::Json& j, record& r) {
            j.at("id").get_to(r.id);
            j.at("book_id").get_to(r.book_id);
            j.at("user_id").get_to(r.user_id);
            from_string(r.creation_time,j.at(record::creation_time_name).get<std::string>());
            from_string(r.stop_time,j.at(record::stop_time_name).get<std::string>());
        }
    };

}


namespace soci {
    using namespace framework::entity;
    template<>
    struct type_conversion<record> {
        typedef values base_type;

        static void from_base(values const &v, indicator const &ind, record &r) {
            if (ind == i_ok) {
                r.id = v.get<db_bigint>("id");
                r.book_id = v.get<db_bigint>("book_id");
                r.user_id = v.get<db_bigint>("user_id");
                r.creation_time = v.get<db_datetime>("creation_time");
                r.stop_time = v.get<db_datetime>("stop_time");
            }
        }

        static void to_base(record const &r, values &v, indicator &ind) {
            v.set("id", r.id);
            v.set("book_id", r.book_id);
            v.set("user_id", r.user_id);
            v.set("creation_time", r.creation_time);
            v.set("stop_time", r.stop_time);

            ind = i_ok;
        }
    };
}
