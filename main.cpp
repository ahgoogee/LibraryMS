//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/application.h"
#include "spdlog/spdlog.h"

int main(){
    spdlog::set_level(spdlog::level::trace);
    auto app = framework::Application();
    app.run();
    return 0;
}