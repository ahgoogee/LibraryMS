//
// Created by ahgoogee on 2023/12/7.
//

#pragma once

#include "string"

namespace common{
    struct BaseFixString{};


    template<char ...C>
    struct FixString:BaseFixString {
        constexpr static std::size_t N = sizeof...(C) + 1;
        constexpr static const char data[N] = {C..., 0};
    };

    template<char ...C>
    auto MakeFixString(FixString<C...>) -> FixString<C...>;

    template<char ...C1, char C, char ...C2>
    auto MakeFixString(FixString<C1...>, FixString<C>, FixString<C2>...) -> decltype(MakeFixString(FixString<C1..., C>{},
                                                                                                   FixString<C2>{}...));

    template<char ...C1, char ...C2>
    auto MakeFixString(FixString<C1...>, FixString<'\0'>, FixString<C2>...) -> FixString<C1...>;


    template<char ...C>
    auto AutoSplitString(FixString<C...>) -> decltype(MakeFixString(FixString<C>{}...));

    template<std::size_t M, std::size_t N>
    constexpr char GetCharFromStr(const char(&arr)[N]) {
        return arr[M < N ? M : N - 1];
    }

}
#define MakeCharIndex(n,str)        common::GetCharFromStr<0x##n##0>(str),common::GetCharFromStr<0x##n##1>(str),\
                                    common::GetCharFromStr<0x##n##2>(str),common::GetCharFromStr<0x##n##3>(str),\
                                    common::GetCharFromStr<0x##n##4>(str),common::GetCharFromStr<0x##n##5>(str),\
                                    common::GetCharFromStr<0x##n##6>(str),common::GetCharFromStr<0x##n##7>(str),\
                                    common::GetCharFromStr<0x##n##8>(str),common::GetCharFromStr<0x##n##9>(str),\
                                    common::GetCharFromStr<0x##n##a>(str),common::GetCharFromStr<0x##n##b>(str),\
                                    common::GetCharFromStr<0x##n##c>(str),common::GetCharFromStr<0x##n##d>(str),\
                                    common::GetCharFromStr<0x##n##e>(str),common::GetCharFromStr<0x##n##f>(str)
#define MakeCharIndex64_L(str)      MakeCharIndex(0,str),MakeCharIndex(1,str),\
                                    MakeCharIndex(2,str),MakeCharIndex(3,str)
#define MakeCharIndex64_H(str)      MakeCharIndex(4,str),MakeCharIndex(5,str),\
                                    MakeCharIndex(6,str),MakeCharIndex(7,str)
#define MakeCharIndexSequence(str)  MakeCharIndex64_L(str),MakeCharIndex64_H(str)
#define MAKESTRINGCHAR(str) decltype(common::MakeFixString(common::FixString<MakeCharIndexSequence(str)>{}))
#define MAKESTRINGTINY(str) decltype(common::AutoSplitString(common::FixString<MakeCharIndexSequence(str)>{}))