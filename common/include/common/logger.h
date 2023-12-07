//
// Created by ahgoogee on 2023/12/5.
//

#pragma once
#include "common/uitls/cstringr.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
//#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/async.h"

namespace common{
    /**
     * std::shared_ptr<spdlog::logger_ptr>的简写
     * */
    using logger_ptr = std::shared_ptr<spdlog::logger>;

    /**
     * 创建默认日志对象,无文件输出,同步
     * */
    static logger_ptr create_logger(){
        return {spdlog::default_logger()};
    }

    /**
     * 创建日志对象
     * @logger_filename: 输出日志文件名
     * @logger_output_directory: 输出日志文件位置
     * @is_async: 是否异步,默认否
     * */
    static logger_ptr create_logger(
            cstringr logger_filename,
            cstringr logger_output_directory,
            bool is_async = false){
        auto log = is_async
                   ? spdlog::basic_logger_mt<spdlog::async_factory>(logger_filename, logger_output_directory)
                   : spdlog::basic_logger_mt(logger_filename, logger_output_directory);
        set_default_logger(log);
        return {log};
    }
}
