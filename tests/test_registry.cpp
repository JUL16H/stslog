#include <catch2/catch_all.hpp>
#include "stslog/stslog.hpp"
#include "TestSink.hpp"

TEST_CASE("test registry basic use", "[Registry]")
{
    auto sink = std::make_shared<stslog::Sinks::TestSink>();
    {
        auto logger = stslog::make_logger("logger for testing registry", {
            {"test sink", sink}
        });
        stslog::LogRegistry::instance().enroll_logger(logger);
    }
    {
        auto logger = stslog::LogRegistry::instance().get_logger("logger for testing registry");
        logger->set_level(stslog::LogLevel::TRACE);
        logger->debug("test");
        REQUIRE(sink->event.msg == "test");
    }
}

TEST_CASE("test registry erase", "[Registry]")
{
    auto logger = stslog::make_logger("logger for testing registry erase");
    stslog::LogRegistry::instance().enroll_logger(logger);
    stslog::LogRegistry::instance().erase_logger("logger for testing registry erase");

    auto empty_logger = stslog::LogRegistry::instance().get_logger("logger for testing registry erase");
    REQUIRE(empty_logger == nullptr);
}
