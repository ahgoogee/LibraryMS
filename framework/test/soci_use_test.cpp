//
// Created by ahgoogee on 2023/12/5.
//

#include <iostream>
#include "soci/soci.h"
#include "soci/mysql/soci-mysql.h"
#include "string"
#include <exception>
#include <algorithm>

int main(){
    using namespace soci;
    try {

        std::cout<< "start" <<std::endl;
        session sql(soci::mysql, "host=61.139.65.141 port=10390 dbname=test user=root password=123456");
        std::cout<< "stop" <<std::endl;

        soci::rowset<soci::row> rs = (sql.prepare << "");


    }
    catch( std::exception& e ){
        std::cout << e.what();
    }



}