//
// Created by ahgoogee on 2023/12/14.
//

#pragma once
#include "framework/entity/entity.h"
#include "soci/soci.h"

namespace framework::entity{
    struct book_type{
    public:
        TABLE(type);
        PK(id);
        COLUMN(id,db_bigint);
        COLUMN(name,db_varchar);
        COLUMN(level,db_int);
        COLUMN(parent_id,db_bigint);
        COLUMN(creation_time,db_datetime);



        friend void to_json(hv::Json& j, const book_type& t) {
            j = hv::Json{
                    {book_type::id_name,t.id},
                    {book_type::name_name, t.name},
                    {book_type::level_name, t.level},
                    {book_type::parent_id_name,t.parent_id},
                    {book_type::creation_time_name,to_string(t.creation_time)  },
            };
        }
        friend void from_json(const hv::Json& j, book_type& t) {
            j.at(book_type::id_name).get_to(t.id);
            j.at(book_type::name_name).get_to(t.name);
            j.at(book_type::level_name).get_to(t.level);
            j.at(book_type::parent_id_name).get_to(t.parent_id);
            from_string(t.creation_time,j.at(book_type::creation_time_name).get<std::string>());
        }
    };


    struct type_ro{
        COLUMN(name,db_varchar);
        COLUMN(level,db_int);
        COLUMN(parent_id,db_bigint);

        friend void to_json(hv::Json& j, const type_ro& t) {
            j = hv::Json{
                    {book_type::name_name, t.name},
                    {book_type::level_name, t.level},
                    {book_type::parent_id_name,t.parent_id},
            };
        }
        friend void from_json(const hv::Json& j, type_ro& t) {
            j.at(book_type::name_name).get_to(t.name);
            j.at(book_type::level_name).get_to(t.level);
            j.at(book_type::parent_id_name).get_to(t.parent_id);
        }
    };
}

namespace soci{
    using namespace framework::entity;
    template<>
    struct type_conversion<book_type>{
        typedef values base_type;

        static void from_base(values const &v, indicator const &ind, book_type &t) {
            if (ind == i_ok) {
                t.id = v.get<db_bigint>(book_type::id_name);
                t.name = v.get<db_varchar>(book_type::name_name);
                t.level = v.get<db_int>(book_type::level_name);
                t.parent_id = v.get<db_bigint>(book_type::parent_id_name);
                t.creation_time = v.get<db_datetime>(book_type::creation_time_name);
            }
        }

        static void to_base(book_type const &t, values &v, indicator &ind) {
            v.set(book_type::id_name,t.id);
            v.set(book_type::name_name, t.name);
            v.set(book_type::level_name,t.level);
            v.set(book_type::parent_id_name,t.parent_id);
            v.set(book_type::creation_time_name,t.creation_time);

            ind = i_ok;
        }
    };
}