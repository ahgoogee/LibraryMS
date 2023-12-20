//
// Created by ahgoogee on 2023/12/18.
//

#pragma once

#include "hv/http_content.h"
#include "page.h"
#include "sort.h"
#include "filter.h"
#include "common/utils.h"

namespace framework::entity{
    struct page_request{
        entity::page page;
        std::vector<entity::sort> sorts;
        std::vector<entity::filter> filters;

        std::string to_sql() const&{
            std::vector<std::string> filter_sql_vec;
            std::for_each(filters.begin(), filters.end(),[&filter_sql_vec](const filter& val){
                filter_sql_vec.push_back(val.to_sql());
            });

            std::vector<std::string> sort_sql_vec;
            std::for_each(sorts.begin(), sorts.end(),[&sort_sql_vec](const sort& val){
                sort_sql_vec.push_back(val.to_sql());
            });

            return fmt::format("{} {} {}",
                               filter_sql_vec.empty() ? "": fmt::format("where {}", common::join(" and ",filter_sql_vec)),
                               sort_sql_vec.empty() ? "" : fmt::format("order by {}", common::join(", ",sort_sql_vec)),
                               fmt::format("limit {}",page.to_sql()));
        }

        std::string to_count_sql() const&{
            std::vector<std::string> filter_sql_vec;
            std::for_each(filters.begin(), filters.end(),[&filter_sql_vec](const filter& val){
                filter_sql_vec.push_back(val.to_sql());
            });

            std::vector<std::string> sort_sql_vec;
            std::for_each(sorts.begin(), sorts.end(),[&sort_sql_vec](const sort& val){
                sort_sql_vec.push_back(val.to_sql());
            });

            return fmt::format("{} {}",
                               filter_sql_vec.empty() ? "": fmt::format("where {}", common::join(" and ",filter_sql_vec)),
                               sort_sql_vec.empty() ? "" : fmt::format("order by {}", common::join(", ",sort_sql_vec)));
        }

        friend void to_json(hv::Json& j, const page_request& t) {
            j = hv::Json{
                    {"page",t.page},
                    {"sorts",t.sorts},
                    {"filters",t.filters},
            };
        }
        friend void from_json(const hv::Json& j, page_request& t) {
            j.at("page").get_to(t.page);
            j.at("sorts").get_to(t.sorts);
            j.at("filters").get_to(t.filters);
        }
    };
}
