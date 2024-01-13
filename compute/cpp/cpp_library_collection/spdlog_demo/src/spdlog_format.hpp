#pragma once

#include "spdlog/spdlog.h"

using  namespace fmt::literals;

void Spdlog_Format()
{

    spdlog::default_logger()->debug("{}", "hello spdlog");

    spdlog::default_logger()->debug("{},{},{}", 'a', 'b', 'c');
    spdlog::default_logger()->debug("{0},{1},{2}", 'a', 'b', 'c');
    spdlog::default_logger()->debug("{0},{1},{2}", 'a', 'b', 'c');
    spdlog::default_logger()->debug("{0}{1}{0}", "abra", "cad");

    spdlog::default_logger()->debug("{:<30}", "left aligned");
    spdlog::default_logger()->debug("{:>30}", "right aligned");
    spdlog::default_logger()->debug("{:^30}", "centered");
    spdlog::default_logger()->debug("{:*^30}", "centered");

    spdlog::default_logger()->debug("Elapsed time {s:.2f} seconds", "s"_a=1.235);


}