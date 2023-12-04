set(MODULE_NAME framework)
message("Build module ${MODULE_NAME}:")

message(STATUS "Enable build test")
enable_testing()
#添加测试文件夹
add_subdirectory(test)

#自动扫描导入涉及到的头文件和源文件
file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
message(STATUS "Include and build files: ${srcs}")
#编译静态库
add_library(${MODULE_NAME} STATIC ${srcs})

#导入头文件信息
target_include_directories(${MODULE_NAME} PUBLIC include)

#导入libhv
find_package(libhv CONFIG REQUIRED)
target_link_libraries(${MODULE_NAME} PUBLIC hv)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${MODULE_NAME} PUBLIC spdlog::spdlog_header_only)