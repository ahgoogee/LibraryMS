//
// Created by ahgoogee on 2023/12/18.
//

#pragma once

#include "hv/http_content.h"
#include "fmt/format.h"

namespace framework::entity{
    struct filter{
        std::string column;
        std::string search_content;

        std::string to_sql() const&{
            return fmt::format("{} like '%{}%'",column,search_content);
        }

        friend void to_json(hv::Json& j, const filter& t) {
            j = hv::Json{
                    {"column",t.column},
                    {"search_content",t.search_content},
            };
        }
        friend void from_json(const hv::Json& j, filter& t) {
            j.at("column").get_to(t.column);
            j.at("search_content").get_to(t.search_content);
        }
    };
}