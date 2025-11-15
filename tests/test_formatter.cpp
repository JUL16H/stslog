#include <catch2/catch_all.hpp>
#include "stslog/stslog.hpp"

TEST_CASE("formatter test", "[formatter]")
{
    stslog::FormatCombiner formatter;
    stslog::LogEvent event {
        .lvl = stslog::LogLevel::INFO,
        .msg = "test msg",
        .threadID = 2342,
        .processID = 2372,
        .time = {
            .year = 2025,
            .month = 11,
            .day = 15,
            .hour = 17,
            .minute = 38,
            .sec = 32,
            .ms = 321
        },
        .pos = {
            .file = "testFile.cpp",
            .func = "testFunc",
            .line = 213
        }
    };

    SECTION("basic format")
    {
        std::string content = formatter.content(event);
        REQUIRE(content == "[17:38:32] [INFO] test msg");
    }

    SECTION("reset format")
    {
        formatter.set_format();
        std::string content = formatter.content(event);
        REQUIRE(content == "[17:38:32] [INFO] test msg");
    }

    SECTION("time")
    {
        formatter.set_format("[%Y-%m-%d %H:%M:%S:%e] [%l] %v");
        std::string content = formatter.content(event);
        REQUIRE(content == "[2025-11-15 17:38:32:321] [INFO] test msg");
    }

    SECTION("pos")
    {
        formatter.set_format("[%f] %f:%L [%l] %v");
        std::string content = formatter.content(event);
        REQUIRE(content == "[testFile.cpp] testFunc:213 [INFO] test msg");
    }
}
