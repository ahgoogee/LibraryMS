//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/application.h"
#include "common/logger.h"

int main(){
    common::logger_ptr log = common::create_logger();

    auto app = framework::Application(log);
    app.run(8080); //阻塞运行
    return 0;
}