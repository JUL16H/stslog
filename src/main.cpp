#include "stslog/stslog.hpp"

int main()
{
    stslog::Logger logger("logger", std::make_shared<stslog::Sinks::StdoutSink>());
    logger.info("hello world");

    return 0;
}
