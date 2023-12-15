//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include <iomanip>
#include "framework/entity/column.h"
#include "framework/common/types.h"
#include "string"
#include "corecrt_wtime.h"
#include "hv/http_content.h"

using namespace common::type;

#define CONSTEXPR_STRING(name,str) public: constexpr static const char * name = str
#define TABLE(name) CONSTEXPR_STRING(table_name,#name)
#define PK(name)    CONSTEXPR_STRING(pk_name,#name)
//#define PROPERTY(name,type) private: type m_##name{}; \
//                            public: const type& get_##name()const&{return m_##name;} \
//                            public: void set_##name(const type& val)&{m_##name = val;}
#define PROPERTY(name,type)public: type name{};
#define COLUMN(name,type)  CONSTEXPR_STRING(name##_name,#name); \
                           PROPERTY(name,type)

//void to_json(hv::Json& j, const std::tm& t) {
//    j = hv::Json{
//            {"year",t.tm_year},
//            {"month",t.tm_mon},
//            {"day",t.tm_mday},
//            {"hour",t.tm_hour},
//            {"minute",t.tm_min},
//            {"second",t.tm_sec}
//    };
//}
//void from_json(const hv::Json& j, std::tm& t) {
//    j.at("year").get_to(t.tm_year);
//    j.at("month").get_to(t.tm_mon);
//    j.at("day").get_to(t.tm_mday);
//    j.at("hour").get_to(t.tm_hour);
//    j.at("minute").get_to(t.tm_min);
//    j.at("second").get_to(t.tm_sec);
//}


std::string to_string(const std::tm& t) {
    std::ostringstream oss;
    oss << std::put_time(&t, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
std::tm& from_string(std::tm& t,const std::string& time_string) {
    std::istringstream iss(time_string);
    iss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    return t;
}