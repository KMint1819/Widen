#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "alan/log.hpp"

namespace alan
{
    std::shared_ptr<spdlog::logger> Log::coreLogger;
    std::shared_ptr<spdlog::logger> Log::appLogger;

    void Log::Init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("alan.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		coreLogger = std::make_shared<spdlog::logger>("ALAN", begin(logSinks), end(logSinks));
		spdlog::register_logger(coreLogger);
		coreLogger->set_level(spdlog::level::trace);
		coreLogger->flush_on(spdlog::level::trace);

		appLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(appLogger);
		appLogger->set_level(spdlog::level::trace);
		appLogger->flush_on(spdlog::level::trace);

        coreLogger->info("Logger initialized");
    }
    std::shared_ptr<spdlog::logger>& Log::GetCoreLogger()
    {
        if(!coreLogger)
            Log::Init();
        
        return coreLogger;
    }

    std::shared_ptr<spdlog::logger>& Log::GetAppLogger()
    {
        if(!appLogger)
            Log::Init();
        
        return appLogger;
    }
}