//
// Created by ahgoogee on 2023/12/19.
//

#pragma once
#include "vector"
#include "framework/entity/book.h"
#include "mapper.h"
#include "common/logger.h"

namespace framework::mapper{
    using namespace framework::entity;
    class book_mapper{
    public:
        static db_bigint add_book(book_ro request,const dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                std::tm now = mapper::now();
                *sql << fmt::format("insert into {0}({1},{2},{3},{4},{5}) values(:{1},:{2},:{3},:{4},{6})", book::table_name
                        ,book::name_name
                        ,book::description_name
                        ,book::type_id_name
                        ,book::creation_time_name
                        ,book::borrow_state_name
                        ,"'未借出'")
                        ,soci::use(request.name)
                        ,soci::use(request.description)
                        ,soci::use(request.type_id)
                        ,soci::use(now);
                db_bigint id;
                sql->get_last_insert_id(book::table_name, id);
                return id;
            }catch (const std::exception& e){
                log->error("sql insert error:{}",e.what());
            }
            throw runtime_exception(403,"创建失败");


        }

        static size_t update_book_by_id(book t, const dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                soci::statement st = (sql->prepare
                        << fmt::format("update {0} set {2}=:{2},{3}=:{3},{4}=:{4} where {1}=:{1}", book::table_name
                                ,book::pk_name
                                ,book::name_name
                                ,book::description_name
                                ,book::type_id_name)
                        , soci::use(t.name)
                        , soci::use(t.description)
                        , soci::use(t.type_id)
                        , soci::use(t.id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql update error:{}",e.what());
            }
            return 0;
        }

        static size_t update_book_borrow_state_by_id(db_bigint id,const std::string& state, const dbsession_ptr& sql,const common::logger_ptr& log){
            try{
                soci::statement st = (sql->prepare
                        << fmt::format("update {0} set {2}=:{2} where {1}=:{1}", book::table_name
                                ,book::pk_name
                                ,book::borrow_state_name)
                        , soci::use(state)
                        , soci::use(id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql update error:{}",e.what());
            }
            return 0;
        }

        static std::vector<book> list_book_by_search(common::cstringr name, const dbsession_ptr& sql,const common::logger_ptr& log){
            std::vector<book> vec;
            try{
                soci::rowset<book> rows= (sql->prepare << fmt::format("select * from {0} where {1} like '%{2}%'",book::table_name
                            ,book::name_name
                            ,name
                    ));

                std::for_each(rows.begin(), rows.end(),[&vec](const book& t){
                    vec.push_back(t);
                });
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            return vec;
        }




    };

}