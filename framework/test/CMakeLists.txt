add_executable(http_server_test http_server_test.cpp)


target_link_libraries(http_server_test framework)


add_test(HttpServerTest http_server_test)
