//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "framework/entity/column.h"
#include "string"

#define TABLE(name) constexpr static const char * table = #name
#define PK(name)    constexpr static const char * pk = #name

