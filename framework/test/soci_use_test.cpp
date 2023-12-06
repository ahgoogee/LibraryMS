//
// Created by ahgoogee on 2023/12/5.
//

#include <iostream>
#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"
#include "string"
#include <exception>

int main(){
    using namespace soci;
    try {

        std::cout<< "start" <<std::endl;
        session sql(soci::mysql, "host=61.139.65.141 port=10390 dbname=test user=root password=123456");
        std::cout<< "stop" <<std::endl;

        std::string first_name = "Steve";
        std::string last_name = "Jobs";
        sql << "insert into person(first_name, last_name)"
               " values(:first_name, :last_name)",
                use(first_name), use(last_name);
        int64_t id;
        sql.get_last_insert_id("Person", id);
    }
    catch( std::exception& e ){
        std::cout << e.what();
    }



}