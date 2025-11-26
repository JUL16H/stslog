#include <catch2/catch_all.hpp>
#include "stslog/stslog.hpp"
#include "TestSink.hpp"

TEST_CASE("test Logger::should_log()", "[Logger]") {
    stslog::Logger logger("logger");
    logger.set_pattern("%v");

    REQUIRE_NOTHROW(logger.trace("test"));

    auto sink = std::make_shared<stslog::Sinks::TestSink>();
    logger.set_level(stslog::LogLevel::WARN);
    logger.add_sink("testSink", sink);
    logger.trace("test");
    logger.debug("test");
    logger.info("test");
    REQUIRE(sink->event.msg.empty());

    logger.warn("test1");
    REQUIRE(sink->event.msg == "test1");

    logger.set_level(stslog::LogLevel::OFF);
    logger.critical("test2");
    REQUIRE(sink->event.msg == "test1");
}

TEST_CASE("test add and erase sink", "[Logger]") {
    stslog::Logger logger("logger");
    auto sink = std::make_shared<stslog::Sinks::TestSink>();

    logger.add_sink("sink", sink);
    logger.erase_sink("sink");
    logger.critical("test");
    REQUIRE(sink->event.content.empty());
}

TEST_CASE("test msg format", "[Logger]") {
    stslog::Logger logger("logger");
    auto sink = std::make_shared<stslog::Sinks::TestSink>();
    logger.add_sink("sink", sink);

    logger.info("{}+{}={}", 2, 3, 5);
    REQUIRE(sink->event.msg == "2+3=5");
}

TEST_CASE("test Logger::set_pattern()", "[Logger]") {
    stslog::Logger logger("logger");

    auto sink1 = std::make_shared<stslog::Sinks::TestSink>();
    auto sink2 = std::make_shared<stslog::Sinks::TestSink>();

    logger.add_sink("sink1", sink1);
    logger.add_sink("sink2", sink2);

    logger.set_pattern("%v");
    logger.critical("test1");
    REQUIRE(sink1->event.content == "test1");
    REQUIRE(sink2->event.content == "test1");

    logger.set_pattern("sink1", "%l");
    logger.warn("test2");
    REQUIRE(sink1->event.content == "WARN");
    REQUIRE(sink2->event.content == "test2");
}
