#pragma once

#include <filesystem>

namespace widen
{

    // TODO: Try to use a singleton class
    namespace config
    {
        namespace port
        {
            extern int message;
        }

        void loadConfigFile(std::filesystem::path);
    }
}