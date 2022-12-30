#pragma once

#include <filesystem>

namespace widen
{
    namespace config
    {
        namespace port
        {
            extern int join;
        }

        void loadConfigFile(std::filesystem::path);
    }
}