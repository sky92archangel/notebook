#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

void Spdlog_Logger()
{
   auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
   console_sink->set_level(spdlog::level::warn);
   
   auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt",true);
   file_sink->set_level(spdlog::level::debug);

   spdlog::logger logger("multi_sink",{console_sink,file_sink});
   logger.set_level(spdlog::level::debug);

   logger.warn("this should appear in both console and file");
   logger.info("this message should not appear in the console , only in the file");
 
}