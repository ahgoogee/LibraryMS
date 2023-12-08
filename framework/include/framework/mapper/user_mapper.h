//
// Created by ahgoogee on 2023/12/8.
//

#pragma once
#include "vector"
#include "framework/entity/user.h"
#include "common/logger.h"
#include "algorithm"

namespace framework::mapper{
    using namespace framework::entity;
    class user_mapper{
    public:

        static std::vector<entity::user> list_all_user(const type::dbsession_ptr& sql,const common::logger_ptr& log){
            std::vector<entity::user> vec;
            try{
                soci::rowset<soci::row> rs = (sql->prepare << fmt::format("select * from {}", entity::user::table_name));
                std::for_each(rs.begin(), rs.end(),[&vec,log](const soci::row& row){
                    vec.emplace_back(row.get<db_bigint>("id"),row.get<db_varchar>("first_name"),row.get<db_varchar>("last_name"));
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

            }catch (std::exception e){
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
                        << fmt::format("update {0} set {1}=:{1},{2}=:{2} where {3}=:{3}", user::table_name,user::first_name_name,user::last_name_name,user::id_name)
                        , soci::use(user.first_name),soci::use(user.last_name),soci::use(user.id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql update error:{}",e.what());
            }
            return 0;
        }


    };
}