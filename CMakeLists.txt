cmake_minimum_required(VERSION 3.14)

project(stslog LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_library(stslog INTERFACE)
target_include_directories(stslog
    INTERFACE
        ${CMAKE_SOURCE_DIR}/include
)

add_executable(stslog_example ${CMAKE_SOURCE_DIR}/examples/main.cpp)
target_link_libraries(stslog_example
    PRIVATE
        stslog
)
set_target_properties(stslog_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/
)

add_subdirectory(external/Catch2)
enable_testing()
add_subdirectory(tests)
