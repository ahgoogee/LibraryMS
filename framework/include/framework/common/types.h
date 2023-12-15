//
// Created by ahgoogee on 2023/12/8.
//

#pragma once
#include "soci/soci.h"
#include "memory"

namespace common::type{
    using dbsession_ptr = std::shared_ptr<soci::session>;

    using db_float = double_t;
    using db_double = double_t;
    using db_decimal = double_t;
    using db_tinyint = int32_t;
    using db_utinyint = int32_t;
    using db_smallint = int32_t;
    using db_usmallint = int32_t;
    using db_int = int32_t;
    using db_uint = uint32_t;
    using db_bigint = int64_t;
    using db_ubigint = uint64_t;
    using db_char = std::string;
    using db_varchar = std::string;
    using db_tinytext = std::string;
    using db_mediumtext = std::string;
    using db_text = std::string;
    using db_longtext = std::string;
    using db_enum = std::string;
    using db_timestamp = std::tm;
    using db_date = std::tm;
    using db_time = std::tm;
    using db_datetime = std::tm;
}
