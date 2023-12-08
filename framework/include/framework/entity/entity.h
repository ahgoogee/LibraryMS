//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "framework/entity/column.h"
#include "framework/common/types.h"
#include "string"
#include "corecrt_wtime.h"

using namespace framework::type;

#define CONSTEXPR_STRING(name,str) public: constexpr static const char * name = str
#define TABLE(name) CONSTEXPR_STRING(table,#name)
#define PK(name)    CONSTEXPR_STRING(pk,#name)
#define PROPERTY(name,type) private: type m_##name{}; \
                            public: const type& get_##name()const&{return m_##name;} \
                            public: void set_##name(const type& val)&{m_##name = val;}
#define COLUMN(name,type)  CONSTEXPR_STRING(name,#name); \
                           PROPERTY(name,type)
