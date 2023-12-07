//
// Created by ahgoogee on 2023/12/7.
//

#pragma once

#include <functional>

namespace common{

    template<typename Ty,typename RTy>
    using transporter = std::function<RTy(Ty&)>;

    template<class Ty,class RTy>
    static RTy operator|(Ty& obj,transporter<Ty,RTy> tra){
        return tra(obj);
    }
}