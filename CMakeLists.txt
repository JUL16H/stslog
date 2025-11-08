cmake_minimum_required(VERSION 3.14)

project(stslog LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_include_directories(main
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
