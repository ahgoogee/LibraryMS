add_executable(http_server_test http_server_test.cpp)
add_executable(soci_use_test soci_use_test.cpp)
add_executable(entity_use_test entity_use_test.cpp)

target_link_libraries(http_server_test framework)
target_link_libraries(entity_use_test framework)
target_link_libraries(soci_use_test framework)
include(${CMAKE_HOME_DIRECTORY}/cmake/copy_file.cmake)
copy_file(${CMAKE_HOME_DIRECTORY}/mysql/lib/libmysql.dll)

add_test(HttpServerTest http_server_test)
add_test(SociUseTest soci_use_test)
add_test(EntityUseTest entity_use_test)
