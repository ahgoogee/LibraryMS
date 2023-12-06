add_executable(http_server_test http_server_test.cpp)
add_executable(soci_use_test soci_use_test.cpp)


target_link_libraries(http_server_test framework)
target_link_libraries(soci_use_test framework)
file(COPY ${CMAKE_HOME_DIRECTORY}/mysql/lib/libmysql.dll DESTINATION .)

add_test(HttpServerTest http_server_test)
add_test(SociUseTest soci_use_test)
