cmake_minimum_required(VERSION 3.16)

project(LibraryMS LANGUAGES CXX)

#添加MSVC编译器选项,使用utf-8
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows" )
    message(STATUS "Add compile options: /utf-8")
    add_compile_options(/utf-8)
endif ()


#配置c++语言设置
set(CMAKE_CXX_STANDARD 11)          # 使用C++ 11 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# 添加编译目标
add_executable(${PROJECT_NAME} main.cpp)