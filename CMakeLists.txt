cmake_minimum_required(VERSION 3.14)

project(stslog LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(stslog INTERFACE)
add_library(stslog::stslog ALIAS stslog)

target_include_directories(stslog
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

option(STSLOG_BUUILD_EXAMPLES "Build stslog examples" ON)
option(STSLOG_BUILD_TESTS "Build stslog tests" ON)

if (STSLOG_BUUILD_EXAMPLES)
    add_executable(stslog_example ${CMAKE_SOURCE_DIR}/examples/main.cpp)
    target_link_libraries(stslog_example
        PRIVATE
            stslog
    )
    set_target_properties(stslog_example PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/examples/
    )
endif()

if (STSLOG_BUILD_TESTS)
    add_subdirectory(external/Catch2)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
