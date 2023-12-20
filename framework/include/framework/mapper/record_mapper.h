//
// Created by ahgoogee on 2023/12/19.
//

#pragma once
#include "vector"
#include "framework/entity/record.h"
#include "framework/entity/user.h"
#include "framework/entity/book.h"
#include "mapper.h"
#include "common/logger.h"
#include "framework/mapper/mapper.h"
#include "framework/mapper/book_mapper.h"

namespace framework::mapper {
    using namespace framework::entity;

    class record_mapper{
    public:
        static db_bigint borrow_to(db_bigint user_id,db_bigint book_id,const dbsession_ptr& sql,const common::logger_ptr& log){
            std::tm stop = mapper::now();
            hv_delay(50);
            std::tm now = mapper::now();

            try{
                //添加记录
                *sql << fmt::format("insert into {0}({1},{2},{3},{4}) values(:{1},:{2},:{3},:{4})", record::table_name
                        ,record::book_id_name
                        ,record::user_id_name
                        ,record::creation_time_name
                        ,record::stop_time_name)
                        ,soci::use(book_id)
                        ,soci::use(user_id)
                        ,soci::use(now)
                        ,soci::use(stop);
                db_bigint id;
                sql->get_last_insert_id(record::table_name, id);

                //修改图书状态
                book_mapper::update_book_borrow_state_by_id(book_id,"borrowed", sql,log);


                return id;
            }catch (const std::exception& e){
                log->error("sql insert error:{}",e.what());
            }
        }

        static bool give_back(db_bigint record_id,const dbsession_ptr& sql,const common::logger_ptr& log){
            std::tm now = mapper::now();
            try{
                //修改记录归还事件
                soci::statement st = (sql->prepare
                        << fmt::format("update {0} set {2}=:{2} where {1}=:{1}", record::table_name
                                ,record::pk_name
                                ,record::stop_time_name)
                        , soci::use(now)
                        , soci::use(record_id));
                st.execute(true);

                //修改图书状态
                auto r = mapper::get_entity_by_id<record>(record_id,sql,log);
                book_mapper::update_book_borrow_state_by_id(r.user_id,"not borrowed", sql,log);

                return st.get_affected_rows();
            }catch (const std::exception& e){
                log->error("sql update error:{}",e.what());
            }
        }


    };


}