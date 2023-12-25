//
// Created by ahgoogee on 2023/12/15.
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

    class admin_mapper{
    public:

        static db_bigint add_admin(admin_ro u,const type::dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                std::tm now = mapper::now();
                db_varchar password = "admin" + u.username;
                *sql << fmt::format("insert into {0}({1},{2},{3}) values(:{1},:{2},:{3})", entity::admin::table_name
                        ,admin::username_name
                        ,admin::creation_time_name
                        ,"password")
                        ,soci::use(u.username)
                        ,soci::use(now)
                        ,soci::use(password);
                db_bigint id;
                sql->get_last_insert_id(admin::table_name, id);
                return id;
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            return -1;
        }

        static size_t update_admin_by_id(entity::admin a, const type::dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                soci::statement st = (sql->prepare
                        << fmt::format("update {0} set {1}=:{1},{2}=:{2} where {3}=:{3}", admin::table_name
                                ,admin::username_name
                                ,admin::creation_time_name
                                ,admin::id_name)
                        , soci::use(a.username)
                        , soci::use(a.creation_time)
                        , soci::use(a.id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql update error:{}",e.what());
            }
            return 0;
        }


    };




}
