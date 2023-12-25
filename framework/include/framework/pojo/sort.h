//
// Created by ahgoogee on 2023/12/18.
//

#pragma once

#include "hv/http_content.h"
#include "fmt/format.h"

namespace framework::entity{
    struct sort{
        std::string column;
        bool is_asc;

        std::string to_sql() const&{
            return fmt::format("{} {}",column,is_asc?"asc":"desc");
        }

        friend void to_json(hv::Json& j, const sort& t) {
            j = hv::Json{
                    {"column",t.column},
                    {"is_asc",t.is_asc},
            };
        }
        friend void from_json(const hv::Json& j, sort& t) {
            j.at("column").get_to(t.column);
            j.at("is_asc").get_to(t.is_asc);
        }
    };
}