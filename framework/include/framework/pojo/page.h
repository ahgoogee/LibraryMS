//
// Created by ahgoogee on 2023/12/18.
//

#pragma once

#include "hv/http_content.h"
#include "fmt/format.h"

namespace framework::entity{
    struct page{
        size_t page_current;
        size_t page_size;

        std::string to_sql() const&{
            return fmt::format("{},{}",page_current*page_size,page_size);
        }


        friend void to_json(hv::Json& j, const page& t) {
            j = hv::Json{
                    {"page_current",t.page_current},
                    {"page_size",t.page_size},
            };
        }
        friend void from_json(const hv::Json& j, page& t) {
            j.at("page_current").get_to(t.page_current);
            j.at("page_size").get_to(t.page_size);
        }
    };
}