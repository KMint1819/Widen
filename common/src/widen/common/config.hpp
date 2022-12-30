#pragma once

#include <filesystem>

namespace widen
{

    // TODO: Maybe try to use a singleton class
    namespace config
    {
        namespace port
        {
            extern int join;
        }

        void loadConfigFile(std::filesystem::path);
    }
}