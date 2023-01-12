#include "widen/common/log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace widen
{
    std::shared_ptr<spdlog::logger> Log::logger;

    void Log::init()
    {
        spdlog::init_thread_pool(8192, 1);
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("/home/widen.log", true));

        logSinks[0]->set_pattern("%^[%T] [%t] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%t] [%l] %n: %v");

        logger = std::make_shared<spdlog::async_logger>("WIDEN", logSinks.begin(), logSinks.end(), spdlog::thread_pool());
        spdlog::register_logger(logger);
        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);

        logger->info("Logger initialized");
    }

    // TODO: check if this implementation is thread-safe
    std::shared_ptr<spdlog::logger> &Log::getLogger()
    {
        if (!logger)
            Log::init();

        return logger;
    }
}