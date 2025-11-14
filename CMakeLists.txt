cmake_minimum_required(VERSION 3.14)

project(stslog LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "_O2")

add_subdirectory(external/Catch2)

add_library(stslog INTERFACE)
target_include_directories(stslog
    INTERFACE
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(main ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(main
    PRIVATE
        stslog
)
