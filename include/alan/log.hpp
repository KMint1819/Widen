#pragma once
#include "spdlog/spdlog.h"

#include "fmt.hpp"

namespace alan
{
    class Log
    {
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger> &GetCoreLogger();
        static std::shared_ptr<spdlog::logger> &GetAppLogger();

    private:
        static std::shared_ptr<spdlog::logger> coreLogger;
        static std::shared_ptr<spdlog::logger> appLogger;
    };
}

// Core log macros
#define ALAN_CORE_TRACE(...)    ::alan::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ALAN_CORE_INFO(...)     ::alan::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ALAN_CORE_WARN(...)     ::alan::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ALAN_CORE_ERROR(...)    ::alan::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ALAN_CORE_CRITICAL(...) ::alan::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ALAN_TRACE(...)         ::alan::Log::GetAppLogger()->trace(__VA_ARGS__)
#define ALAN_INFO(...)          ::alan::Log::GetAppLogger()->info(__VA_ARGS__)
#define ALAN_WARN(...)          ::alan::Log::GetAppLogger()->warn(__VA_ARGS__)
#define ALAN_ERROR(...)         ::alan::Log::GetAppLogger()->error(__VA_ARGS__)
#define ALAN_CRITICAL(...)      ::alan::Log::GetAppLogger()->critical(__VA_ARGS__)