//
// Created by ahgoogee on 2023/12/19.
//

#pragma once
#include "vector"
#include "framework/entity/type.h"
#include "mapper.h"
#include "common/logger.h"

namespace framework::mapper{
    using namespace framework::entity;
    class type_mapper{
    public:
        static db_bigint add_type(type_ro request,const dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                std::tm now = mapper::now();
                *sql << fmt::format("insert into {0}({1},{2},{3},{4}) values(:{1},:{2},:{3},:{4})", book_type::table_name
                        ,book_type::name_name
                        ,book_type::level_name
                        ,book_type::parent_id_name
                        ,book_type::creation_time_name)
                        ,soci::use(request.name)
                        ,soci::use(request.level)
                        ,soci::use(request.parent_id)
                        ,soci::use(now);
                db_bigint id;
                sql->get_last_insert_id(book_type::table_name, id);
                return id;
            }catch (const std::exception& e){
                log->error("sql insert error:{}",e.what());
            }
            throw runtime_exception(403,"创建失败");
        }


        static size_t update_type_by_id(book_type t, const dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                soci::statement st = (sql->prepare
                        << fmt::format("update {0} set {2}=:{2},{3}=:{3},{4}=:{4} where {1}=:{1}", book_type::table_name
                                ,book_type::pk_name
                                ,book_type::name_name
                                ,book_type::level_name
                                ,book_type::parent_id_name)
                        , soci::use(t.name)
                        , soci::use(t.level)
                        , soci::use(t.parent_id)
                        , soci::use(t.id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql update error:{}",e.what());
            }
            return 0;
        }


        static std::vector<book_type> list_type_by_search(db_int level,common::cstringr name, const dbsession_ptr& sql,const common::logger_ptr& log){
            std::vector<book_type> vec;
            try{
                soci::rowset<book_type> rows;
                if(level == -1){
                    rows = (sql->prepare << fmt::format("select * from {0} where {1} like '%{2}%'",book_type::table_name
                            ,book_type::name_name
                            ,name));
                } else{
                    rows = (sql->prepare << fmt::format("select * from {0} where {1} like '%{2}%' and {3}=:{3}",book_type::table_name
                            ,book_type::name_name
                            ,name
                            ,book_type::level_name
                    ),soci::use(level));
                }

                std::for_each(rows.begin(), rows.end(),[&vec](const book_type& t){
                    vec.push_back(t);
                });
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            return vec;
        }
    };



}