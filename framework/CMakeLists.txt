set(MODULE_NAME framework)
message("Build module ${MODULE_NAME}:")

message(STATUS "Enable build test")
enable_testing()
#添加测试文件夹
add_subdirectory(test)

include(cmake/copy_dll.cmake)
#添加findXXX.cmake搜索路径
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_LIST_DIR}/cmake")

#自动扫描导入涉及到的头文件和源文件
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
message(STATUS "Include and build files: ${srcs}")
#编译静态库
add_library(${MODULE_NAME} STATIC ${srcs})

#导入头文件信息
target_include_directories(${MODULE_NAME} PUBLIC include)

#导入mysql connector
set(MYSQL_ROOT_DIR ${CMAKE_HOME_DIRECTORY}/mysql)
target_include_directories(${MODULE_NAME} PUBLIC ${MYSQL_ROOT_DIR}/include)
target_link_directories(${MODULE_NAME} PUBLIC ${MYSQL_ROOT_DIR}/lib)
target_link_libraries(${MODULE_NAME} PUBLIC libmysql mysqlclient)


#导入libhv
find_package(libhv CONFIG REQUIRED)
target_link_libraries(${MODULE_NAME} PUBLIC hv)

#导入soci
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_HOME_DIRECTORY}/soci/")
find_package(SOCI CONFIG REQUIRED)
target_link_libraries(${MODULE_NAME} PUBLIC SOCI::soci_core_static  SOCI::soci_mysql_static)
