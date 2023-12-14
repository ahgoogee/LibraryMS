//
// Created by ahgoogee on 2023/12/14.
//

#pragma once
#include "framework/entity/entity.h"
#include "soci/soci.h"

namespace framework::entity{
    struct book{
    public:
        TABLE(book);
        PK(id);
        COLUMN(id,db_bigint);
        COLUMN(name,db_varchar);
        COLUMN(description,db_text);
        COLUMN(image,db_varchar);
        COLUMN(type_id,db_bigint);
        COLUMN(borrow_state,db_varchar);
        COLUMN(creation_time,db_datetime);


        friend void to_json(hv::Json &j,const book &b){
            j = {
                    {book::id_name,b.id},
                    {book::name_name,b.name},
                    {book::description_name,b.description},
                    {book::image_name,b.image},
                    {book::type_id_name,b.type_id},
                    {book::borrow_state_name,b.borrow_state},
                    {book::creation_time_name,to_string(b.creation_time)}
            };
        }

        friend void from_json(const hv::Json& j, book& b) {
            j.at("id").get_to(b.id);
            j.at("name").get_to(b.name);
            j.at("description").get_to(b.description);
            j.at("image").get_to(b.image);
            j.at("type_id").get_to(b.type_id);
            j.at("borrow_state").get_to(b.borrow_state);
            from_string(b.creation_time,j.at(book::creation_time_name).get<std::string>());
        }


    };

}

namespace soci {
    using namespace framework::entity;
    template<>
    struct type_conversion<book> {
        typedef values base_type;

        static void from_base(values const &v, indicator const &ind, book &b) {
            if (ind == i_ok) {
                b.id = v.get<db_bigint>("id");
                b.name = v.get<db_varchar>("name");
                b.description = v.get<db_text>("description");
                b.image = v.get<db_varchar>("image");
                b.type_id = v.get<db_bigint>("type_id");
                b.borrow_state = v.get<db_varchar>("borrow_state");
                b.creation_time = v.get<db_datetime>(book::creation_time_name);
            }
        }

        static void to_base(book const &b, values &v, indicator &ind) {
            v.set("id", b.id);
            v.set("name", b.name);
            v.set("description", b.description);
            v.set("image", b.image);
            v.set("type_id", b.type_id);
            v.set("borrow_state", b.borrow_state);
            v.set(book::creation_time_name,b.creation_time);

            ind = i_ok;
        }
    };
}
