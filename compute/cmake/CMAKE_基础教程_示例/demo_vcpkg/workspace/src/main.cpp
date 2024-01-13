
#include <iostream>

#include "spdlog/spdlog.h"
 
using namespace fmt::literals;

inline void Spdlog_Basic()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::default_logger()->debug("hello spdlog");
}

int main(int argc, char argv[])
{
    Spdlog_Basic();
    return 0;
}