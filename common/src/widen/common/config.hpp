#pragma once

#include <filesystem>

namespace widen
{

    // TODO: Try to use a singleton class
    namespace config
    {
        namespace port
        {
            extern int introducer;
            extern int failureDetection;
            extern int distributedFS;
        }

        void loadConfigFile(std::filesystem::path);
    }
}