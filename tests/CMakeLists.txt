file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(stslog_tests ${TEST_SOURCES})
target_link_libraries(stslog_tests
    PRIVATE
        stslog
        Catch2::Catch2WithMain
)
