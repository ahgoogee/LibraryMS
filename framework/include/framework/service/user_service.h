//
// Created by ahgoogee on 2023/12/5.
//

#pragma once

#include "framework/service/service.h"
#include "framework/application.h"
#include "framework/common/access_assert.h"
#include "framework/common/runtime_exception.h"
#include "framework/pojo/token.h"
#include "framework/mapper/mapper.h"
#include "framework/mapper/user_mapper.h"
#include "framework/mapper/admin_mapper.h"


namespace framework::service{
    using namespace entity;

    class user_service{
    public:
        static void register_service(hv::HttpService &_router,framework::Application& app){
            service serv(_router);

            ::common::logger_ptr log = app.log;
            std::shared_ptr<soci::session> sql = app.sql;

            serv.POST<std::string>("/login",[sql,log](const HttpContextPtr &ctx){
                std::string username;
                std::string password;
                std::string usertype;
                hv::Json json = ctx->json();
                json.at("username").get_to(username);
                json.at("password").get_to(password);
                json.at("usertype").get_to(usertype);

                int count = 0;
                // 根据usertype确认用户所在表
                std::string table = usertype == "admin"
                                    ? entity::admin::table_name
                                    : entity::user::table_name;
                *sql << fmt::format("select count(*) from {0} where {1}=:{1}", table,"username")
                        ,soci::use(username),soci::into(count);

                //没有找到目标用户
                if(count <= 0 ) throw runtime_exception(401,"不存在");
                try{
                    db_varchar db_passwd;
                    db_bigint id;
                    *sql << fmt::format("select {0},{1} from {2} where {3}=:{3}","password","id", table,"username")
                            ,soci::use(username)
                            ,soci::into(db_passwd)
                            ,soci::into(id);
                    if(!db_passwd.empty() && password == db_passwd){
                        entity::token t{id,username,usertype};

                        using base64 = cppcodec::base64_rfc4648;
                        std::string token = base64::encode(to_string(hv::Json{t}));
                        return result<std::string>::ok(token);
                    }
                }catch (const std::exception& e){
                    log->error("login error:{}",e.what());
                }

                //能找到用户,但是密码比对错误
                throw runtime_exception(20001,"密码错误");
            });

            serv.POST<db_bigint>("/register",[sql,log](const HttpContextPtr &ctx){
                std::string username;
                std::string password;
                hv::Json json = ctx->json();
                json.at("username").get_to(username);
                json.at("password").get_to(password);

                int count = 0;
                *sql << fmt::format("select count(*) from {0} where {1}=:{1}", user::table_name,"username")
                        ,soci::use(username),soci::into(count);
                //找到目标用户
                if(count > 0 ) throw runtime_exception(403,"用户已存在");

                try{
                    db_bigint id;
                    std::tm now = framework::mapper::mapper::now();
                    *sql << fmt::format("insert into {0}({1},{2},{3}) values(:{1},:{2},:{3})",user::table_name
                                        , user::username_name
                                        , "password"
                                        , user::creation_time_name)
                            ,soci::use(username)
                            ,soci::use(password)
                            ,soci::use(now);
                    sql->get_last_insert_id(user::table_name, id);
                    return result<db_bigint>::ok(id);
                }catch (const std::exception& e){
                    log->error("login error:{}",e.what());
                }
                throw runtime_exception(403,"创建失败");
            });

            serv.POST<std::vector<user>>("/list_user_by_id_list",[sql,log](const HttpContextPtr &ctx){
                std::vector<db_bigint> id_list;
                auto j = ctx->json();
                j.at("id_list").get_to(id_list);

                std::vector<user> users = mapper::mapper::list_entity_by_id_list<user>(id_list,sql,log);
                return result<std::vector<user>>::ok(users);

            });

            serv.POST<std::vector<admin>>("/list_admin_by_id_list",[sql,log](const HttpContextPtr &ctx){
                std::vector<db_bigint> id_list;
                auto j = ctx->json();
                j.at("id_list").get_to(id_list);

                std::vector<admin> vec = mapper::mapper::list_entity_by_id_list<admin>(id_list,sql,log);
                return result<std::vector<admin>>::ok(vec);

            });

            serv.POST<db_bigint>("/add_user", [sql,log](const HttpContextPtr &ctx){
                user_ro u;
                auto j = ctx->json();
                j.at("username").get_to(u.username);


                db_bigint id = mapper::user_mapper::add_user(u,sql,log);
                return result<db_bigint>::ok(id);
            });

            //仅admin
            serv.POST<db_bigint>("/add_admin", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                admin_ro u;
                auto j = ctx->json();
                j.at("username").get_to(u.username);

                db_bigint id = mapper::admin_mapper::add_admin(u,sql,log);
                return result<db_bigint>::ok(id);
            });

            serv.GET<std::vector<user>>("/list_user", [sql,log](const HttpContextPtr &ctx){
                std::vector<user> vec = mapper::mapper::list_all_entity<user>(sql,log);
                return result<std::vector<user>>::ok(vec);
            });

            //仅admin
            serv.GET<std::vector<admin>>("/list_admin", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                std::vector<admin> vec = mapper::mapper::list_all_entity<admin>(sql,log);
                return result<std::vector<admin>>::ok(vec);
            });

            serv.GET<user>("/get_user_by_username", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("username").empty()) throw runtime_exception{403,"username错误"};
                std::string username = ctx->param("username");

                user u;
                try{
                    *sql << fmt::format("select * from {} where {}='{}' limit 1", user::table_name,user::username_name,username)
                    ,soci::into(u);

                }catch (const std::exception& e){
                    log->error("sql select error:{}",e.what());
                }
                return result<user>::ok(u);
            });

            serv.GET<admin>("/get_admin_by_username", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("username").empty()) throw runtime_exception{403,"username错误"};
                std::string username = ctx->param("username");

                admin u;
                try{
                    *sql << fmt::format("select * from {} where {}='{}' limit 1", admin::table_name,admin::username_name,username)
                            ,soci::into(u);

                }catch (const std::exception& e){
                    log->error("sql select error:{}",e.what());
                }
                return result<admin>::ok(u);
            });

            serv.GET<user>("/get_user_by_id", [sql,log](const HttpContextPtr &ctx){
                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                user u = mapper::mapper::get_entity_by_id<user>(id,sql,log);
                return result<user>::ok(u);
            });

            //仅admin
            serv.GET<admin>("/get_admin_by_id", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                admin u = mapper::mapper::get_entity_by_id<admin>(id,sql,log);
                return result<admin>::ok(u);
            });

            //仅admin
            serv.GET<bool>("/delete_user_by_id", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                size_t num = mapper::mapper::delete_entity_by_id<user>(id,sql,log);
                return result<bool>::ok(num);
            });

            //仅admin
            serv.GET<bool>("/delete_admin_by_id", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                if(ctx->param("id").empty()) throw runtime_exception{403,"id错误"};

                int id = stoi(ctx->param("id"));
                size_t num = mapper::mapper::delete_entity_by_id<admin>(id,sql,log);
                return result<bool>::ok(num);
            });

            serv.POST<bool>("/update_user_by_id", [sql,log](const HttpContextPtr &ctx){
                user u;
                ctx->json().get_to(u);
                size_t num = mapper::user_mapper::update_user_by_id(u,sql,log);
                return result<bool>::ok(num);
            });

            //仅admin
            serv.POST<bool>("/update_admin_by_id", [sql,log](const HttpContextPtr &ctx){
                //common::access_assert("admin");

                admin u;
                ctx->json().get_to(u);
                size_t num = mapper::admin_mapper::update_admin_by_id(u,sql,log);
                return result<bool>::ok(num);
            });


            serv.POST<std::vector<user>>("/list_user_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                std::vector<user> res = mapper::mapper::list_entity_by_page<user>(request,sql,log);
                return result<std::vector<user>>::ok(res);
            });
            serv.POST<size_t>("/count_user_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                size_t res = mapper::mapper::count_entity_by_page<user>(request,sql,log);
                return result<size_t>::ok(res);
            });


            serv.POST<std::vector<admin>>("/list_admin_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                std::vector<admin> res = mapper::mapper::list_entity_by_page<admin>(request,sql,log);
                return result<std::vector<admin>>::ok(res);
            });
            serv.POST<size_t>("/count_admin_by_page",[sql,log](const HttpContextPtr &ctx){
                page_request request;
                ctx->json().get_to(request);

                size_t res = mapper::mapper::count_entity_by_page<admin>(request,sql,log);
                return result<size_t>::ok(res);
            });

        }
    };




}




