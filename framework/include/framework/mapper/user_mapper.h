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
#include "framework/pojo/token.h"
#include "mapper.h"

namespace framework::mapper{
    using namespace framework::entity;
    class user_mapper{
    public:

        static db_bigint add_user(user_ro u,const type::dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                std::tm now = mapper::now();
                db_varchar password = "lms" + u.username;
                *sql << fmt::format("insert into {0}({1},{2},{3}) values(:{1},:{2},:{3})", entity::user::table_name
                                    ,user::username_name
                                    ,user::creation_time_name
                                    ,"password")
                                    ,soci::use(u.username)
                                    ,soci::use(now)
                                    ,soci::use(password);
                db_bigint id;
                sql->get_last_insert_id(user::table_name, id);
                return id;
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            throw runtime_exception(403,"创建失败");
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