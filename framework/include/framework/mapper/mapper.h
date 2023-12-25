//
// Created by ahgoogee on 2023/12/15.
//

#pragma once

#include "framework/common/types.h"
#include "common/logger.h"
#include "framework/common/runtime_exception.h"
#include "framework/pojo/page_request.h"

namespace framework::mapper{
    using namespace common;

    class mapper{
    public:

        template<class E>
        static E get_entity_by_id(type::db_bigint id, const type::dbsession_ptr& sql,const common::logger_ptr& log){
            E entity;
            type::db_int count = 0;

            *sql << fmt::format("select count(*) from {0} where {1}=:{1}", E::table_name,E::id_name)
                    ,soci::use(id),soci::into(count);

            log->info("select count:{}",count);
            if(!count) throw runtime_exception(401,"不存在");

            try{
                *sql << fmt::format("select * from {0} where {1}=:{1}", E::table_name,E::id_name)
                        ,soci::use(id),soci::into(entity);

            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }


            return entity;
        }

        template<class E>
        static size_t delete_entity_by_id(int id, const type::dbsession_ptr& sql,const common::logger_ptr& log){
            E entity;
            try{
                soci::statement st = (sql->prepare << fmt::format("delete from {0} where {1}=:{1}", E::table_name,E::id_name)
                        , soci::use(id));
                st.execute(true);
                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql delete error:{}",e.what());
            }
            return 0;
        }

        template<class E>
        static std::vector<E> list_all_entity(const type::dbsession_ptr& sql,const common::logger_ptr& log){
            std::vector<E> vec;
            try{
                soci::rowset<E> rs = (sql->prepare << fmt::format("select * from {}", E::table_name));
                std::for_each(rs.begin(), rs.end(),[&vec](const E& row){
                    vec.push_back(row);
                });
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            return vec;
        }

        template<class E>
        static std::vector<E> list_entity_by_id_list(std::vector<type::db_bigint> id_list, const type::dbsession_ptr& sql,const common::logger_ptr& log){
            std::vector<E> vec;
            std::vector<std::string> id_string_list;
            std::for_each(id_list.begin(), id_list.end(),[&id_string_list](type::db_bigint id){
                id_string_list.push_back(fmt::format("{}",id));
            });
            try{
                std::string sql_string = fmt::format("select * from {0} where {1} in ({2})", E::table_name
                        ,E::pk_name
                        ,common::join(",",id_string_list)
                );
                log->debug("list_entity_by_id_list:sql_string:{}", sql_string);
                soci::rowset<E> rs = (sql->prepare << sql_string);
                std::for_each(rs.begin(), rs.end(),[&vec](const E& row){
                    vec.push_back(row);
                });
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }
            return vec;
        }


        static std::tm now(){
            std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime);
            return {*localTime};
        }

        template<class E>
        static std::vector<E> list_entity_by_page(entity::page_request request,const type::dbsession_ptr& sql,const common::logger_ptr& log){
            std::vector<E> vec;
            try{
                std::string page_sql = request.to_sql();
                log->debug("list_entity_by_page[page_sql]:{}",page_sql);
                soci::rowset<E> rs = (sql->prepare << fmt::format("select * from {} {}", E::table_name,page_sql));
                std::for_each(rs.begin(), rs.end(),[&vec](const E& row){
                    vec.push_back(row);
                });
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }

            return vec;
        }

        template<class E>
        static size_t count_entity_by_page(entity::page_request request,const type::dbsession_ptr& sql,const common::logger_ptr& log){
            size_t count;
            try{
                std::string page_sql = request.to_count_sql();
                log->debug("list_entity_by_page[count_page_sql]:{}",page_sql);

                *sql << fmt::format("select count(*) from {} {}", E::table_name,page_sql),soci::into(count);
            }catch (const std::exception& e){
                log->error("sql select error:{}",e.what());
            }

            return count;
        }
    };






}