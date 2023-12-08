//
// Created by ahgoogee on 2023/12/4.
//

#include "framework/application.h"
#include "common/logger.h"
#include "common/toml.hpp"

///server
static int32_t g_export_port = 8080;

///mysql
static std::string g_mysql_host = "127.0.0.1";
static int32_t g_mysql_port = 3306;
static std::string g_dbname = "sys";
static std::string g_user = "root";
static std::string g_password;
static std::string g_db_string;

///logger
static spdlog::level::level_enum g_log_level = spdlog::level::info;
static bool g_enable_file_out = false;
static std::string g_output_directory;
static std::string g_output_filename;


void parse_config(const char*);

int main(int argn,char** args){
    parse_config("libraryms.toml");

    common::logger_ptr log = common::create_logger();
    if(g_enable_file_out && !g_output_directory.empty() && !g_output_filename.empty())
        log = common::create_logger(g_output_filename,g_output_directory,true);
    log->set_level(g_log_level);

    auto app = framework::Application(g_db_string,log);
    app.run(g_export_port); //阻塞运行
    return 0;
}

void parse_config(const char* filename){
    ///server
    int32_t export_port;

    ///mysql
    std::string mysql_host;
    int32_t mysql_port;
    std::string dbname;
    std::string user;
    std::string password;
    std::string db_string;

    ///logger
    spdlog::level::level_enum log_level;
    bool enable_file_out;
    std::string output_directory;
    std::string output_filename;


    toml::table table;
    try{
        table = toml::parse_file(filename);
        export_port = table["backend"]["export_port"].value_or(g_export_port);
        mysql_host = table["backend"]["mysql"]["host"].value_or(g_mysql_host);
        mysql_port = table["backend"]["mysql"]["port"].value_or(g_mysql_port);
        dbname = table["backend"]["mysql"]["dbname"].value_or(g_dbname);
        user = table["backend"]["mysql"]["user"].value_or(g_user);
        password = table["backend"]["mysql"]["password"].value_or(g_password);
        db_string = fmt::format("host={} port={} dbname={} user={} password={}",mysql_host,mysql_port,dbname,user,password);
        std::string log_level_str = table["backend"]["logger"]["log_level"].value_or("info");
        enable_file_out = table["backend"]["logger"]["enable_file_out"].value_or(g_enable_file_out);
        output_filename = table["backend"]["logger"]["output_filename"].value_or(g_output_filename);
        output_directory = table["backend"]["logger"]["output_directory"].value_or(g_output_directory);

        std::map<std::string,spdlog::level::level_enum> level_mapper{
                {"trace",spdlog::level::trace},
                {"debug",spdlog::level::debug},
                {"info",spdlog::level::info},
                {"warn",spdlog::level::warn},
                {"error",spdlog::level::err},
        };
        log_level = level_mapper[log_level_str];

    }catch (const std::exception& err)
    {
        std::cerr << "Parsing failed:\n" << err.what() << "\n";
        return;
    }

    ///server
    g_export_port = export_port;

    ///mysql
    g_mysql_host = mysql_host;
    g_mysql_port = mysql_port;
    g_dbname = dbname;
    g_user = user;
    g_password = password;
    g_db_string = db_string;

    ///logger
    g_log_level = log_level;
    g_enable_file_out = enable_file_out;
    g_output_directory = output_directory;
    g_output_filename = output_filename;
}