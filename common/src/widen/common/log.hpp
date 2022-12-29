#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/fmt/bundled/chrono.h>
#include <spdlog/fmt/bundled/ranges.h>

#include "fmt.hpp"

namespace widen
{
    class Log
    {
    public:
        /**
         * @brief Get the Logger object
         *
         * @return std::shared_ptr<spdlog::logger>&
         */
        static std::shared_ptr<spdlog::logger> &getLogger();

    private:
        static std::shared_ptr<spdlog::logger> logger;
        static void init();
    };
}

// log macros
#define WIDEN_TRACE(...) ::widen::Log::getLogger()->trace(__VA_ARGS__)
#define WIDEN_INFO(...) ::widen::Log::getLogger()->info(__VA_ARGS__)
#define WIDEN_WARN(...) ::widen::Log::getLogger()->warn(__VA_ARGS__)
#define WIDEN_ERROR(...) ::widen::Log::getLogger()->error(__VA_ARGS__)
#define WIDEN_CRITICAL(...) ::widen::Log::getLogger()->critical(__VA_ARGS__)
