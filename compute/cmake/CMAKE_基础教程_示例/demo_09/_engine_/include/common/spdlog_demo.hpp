#pragma once



#include "spdlog/spdlog.h" 
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

using  namespace fmt::literals;
// #include "spdlog/spdlog.h"

inline void Spdlog_Basic()
{
    spdlog::set_level(spdlog::level::debug);
    spdlog::default_logger()->debug("hello spdlog");
}


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