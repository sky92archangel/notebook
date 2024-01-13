#pragma once

#include "spdlog/spdlog.h"


void Spdlog_Basic()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::default_logger()->debug("hello spdlog");
}