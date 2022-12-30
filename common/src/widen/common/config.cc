#include <yaml-cpp/yaml.h>

#include "widen/common/config.hpp"
#include "widen/common/log.hpp"

namespace widen
{
    namespace config
    {
        namespace port
        {
            int join = 9999;
        }

        void loadConfigFile(std::filesystem::path configFile)
        {
            configFile = std::filesystem::absolute(configFile);
            try
            {
                YAML::Node node = YAML::LoadFile(configFile.string());
                port::join = node["port"]["join"].as<int>();
            }
            catch (YAML::BadFile &e)
            {
                WIDEN_ERROR("Bad file {}: {}", configFile.string(), e.what());
                throw e;
            }
            catch (YAML::ParserException &e)
            {
                WIDEN_ERROR("Parse error of file {}: {}", configFile.string(), e.what());
                throw e;
            }
        }
    }
}