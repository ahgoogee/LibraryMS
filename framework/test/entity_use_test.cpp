//
// Created by ahgoogee on 2023/12/6.
//

#include <iostream>
#include <type_traits>
#include <array>
#include "framework/entity/column.h"
#include "functional"
#include "common/uitls/constexpr_string.h"

using namespace framework;
using namespace common;


int main(){

    auto a = FixString<'a','b'>();

    auto b = FixString<'a','c'>();

    auto aaa = GetCharFromStr<0>("123");
    auto bbb = GetCharFromStr<0>("124");


    std::cout << (std::is_same_v<decltype(a), decltype(b)> ? "same":"no same") << std::endl;
    std::cout << (aaa == bbb? "same":"no same") << std::endl;
    std::cout << (std::is_same_v<MAKESTRINGCHAR("abv"),MAKESTRINGCHAR("abc")>? "same":"no same") << std::endl;
    std::cout << (std::is_same_v<MAKESTRINGTINY("abc"),MAKESTRINGTINY("abc")>? "same":"no same") << std::endl;
    std::cout << MAKESTRINGCHAR("abv")::N << std::endl;
    std::cout << MAKESTRINGTINY("abv")::N << std::endl;


    auto col2 = COLUMN(double,"age")(true);
    auto col = entity::column<int,MAKESTRINGTINY("name")>(true);
    std::cout << col.is_nullable << std::endl;
    std::cout << decltype(col)::name::data << std::endl;
    std::cout << typeid(decltype(col)::type).name() << std::endl;

}