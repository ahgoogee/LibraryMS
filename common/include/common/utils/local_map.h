//
// Created by ahgoogee on 2023/12/14.
//

#pragma once

#include <string>
#include <map>
#include <thread>

namespace common{
    namespace local_map{
        static std::map<std::thread::id,std::map<std::string,std::string>> local_map_pool;
        
        static std::map<std::string,std::string>& local(){
            std::thread::id threadId = std::this_thread::get_id();

            if(local_map_pool.find(threadId) == local_map_pool.end()){
                local_map_pool[threadId] = {};
            }
            return local_map_pool[threadId];
        }

        static void release(){
            std::thread::id threadId = std::this_thread::get_id();
            if(local_map_pool.find(threadId) == local_map_pool.end())return;
            local_map_pool.erase(threadId);
        }
    };
}