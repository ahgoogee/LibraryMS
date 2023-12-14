//
// Created by ahgoogee on 2023/12/8.
//

#pragma once
#include "vector"
#include "framework/entity/user.h"
#include "common/logger.h"
#include "algorithm"
#include "framework/entity/admin.h"
#include "cppcodec/base64_rfc4648.hpp"
#include "framework/entity/token.h"

namespace framework::mapper{
    using namespace framework::entity;
    class user_mapper{
    public:
        static std::string login(common::cstringr username,common::cstringr password,common::cstringr usertype
                                 ,const type::dbsession_ptr& sql,const common::logger_ptr& log){

            int count = 0;
            std::string table = usertype == "admin"
                    ? entity::admin::table_name
                    : entity::user::table_name;
            *sql << fmt::format("select count(*) from {0} where {1}=:{1}", table,entity::user::username_name)
                    ,soci::use(username),soci::into(count);

            if(count <= 0 ) throw runtime_exception(401,"不存在");
            try{
                db_varchar db_passwd;
                db_bigint id;
                *sql << fmt::format("select {0},{1} from {2} where {3}=:{3}","password",user::pk_name, table,user::username_name)
                        ,soci::use(username)
                        ,soci::into(db_passwd)
                        ,soci::into(id);
                if(!db_passwd.empty() && password == db_passwd){
                    entity::token t{id,username,usertype};

                    using base64 = cppcodec::base64_rfc4648;
                    return base64::encode(to_string(hv::Json{t}));
                }
            }catch (const std::exception& e){
                log->error("login error:{}",e.what());
            }


            throw runtime_exception(20001,"密码错误");
        }


        static db_bigint add_user(user u,const type::dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                *sql << fmt::format("insert into {0}({1},{2}) values(:{1},:{2})", entity::user::table_name
                                    ,user::username_name
                                    ,user::creation_time_name)
                                    ,soci::use(u.username)
                                    ,soci::use(u.creation_time);
                db_bigint id;
                sql->get_last_insert_id("Person", id);
                return id;
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            return -1;
        }

        static std::vector<entity::user> list_all_user(const type::dbsession_ptr& sql,const common::logger_ptr& log){
            std::vector<entity::user> vec;
            try{
                soci::rowset<soci::row> rs = (sql->prepare << fmt::format("select * from {}", entity::user::table_name));
                std::for_each(rs.begin(), rs.end(),[&vec,log](const soci::row& row){
                    user u;
                    u.id = row.get<db_bigint>(user::id_name);
                    u.username = row.get<db_varchar>(user::username_name);
                    u.creation_time = row.get<db_datetime>(user::creation_time_name);

                    vec.push_back(u);

                    //vec.emplace_back(row.get<db_bigint>("id"),row.get<db_varchar>("first_name"),row.get<db_varchar>("last_name"));
                });
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            return vec;
        }

        static entity::user get_user_by_id(int id, const type::dbsession_ptr& sql,const common::logger_ptr& log){
            entity::user user;
            db_int count = 0;

            *sql << fmt::format("select count(*) from {0} where {1}=:{1}", entity::user::table_name,entity::user::id_name)
                    ,soci::use(id),soci::into(count);

            log->info("select count:{}",count);
            if(!count) throw runtime_exception(401,"不存在");

            try{
                *sql << fmt::format("select * from {0} where {1}=:{1}", user::table_name,user::id_name)
                ,soci::use(id),soci::into(user);

            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }


            return user;
        }

        static size_t delete_user_by_id(int id, const type::dbsession_ptr& sql,const common::logger_ptr& log){
            entity::user user;
            try{
                soci::statement st = (sql->prepare << fmt::format("delete from {0} where {1}=:{1}", user::table_name,user::id_name)
                        , soci::use(id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql delete error:{}",e.what());
            }
            return 0;
        }

        static size_t update_user_by_id(entity::user user, const type::dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                soci::statement st = (sql->prepare
                        << fmt::format("update {0} set {1}=:{1},{2}=:{2} where {3}=:{3}", user::table_name
                                       ,user::username_name
                                       ,user::creation_time_name
                                       ,user::id_name)
                        , soci::use(user.username)
                        , soci::use(user.creation_time)
                        , soci::use(user.id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql update error:{}",e.what());
            }
            return 0;
        }


    };
}