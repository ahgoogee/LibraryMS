//
// Created by ahgoogee on 2023/12/6.
//

#pragma once

#include <string>
#include "common/utils.h"
#include "type_traits"


namespace framework::entity{

    struct base_column{};
    template<typename Ty, typename FSTy,bool IsNullable,
            typename EntityTy,
            typename = std::enable_if_t<std::is_base_of_v<common::BaseFixString,FSTy>>
    >
    struct column:base_column{
        using name = FSTy;
        using type = Ty;
        constexpr static bool is_nullable = IsNullable;

        Ty EntityTy::*addr;
        column() = default;
        explicit column(Ty EntityTy::*_addr):addr(_addr){}
    };

}



