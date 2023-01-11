#include <yaml-cpp/yaml.h>

#include "widen/common/config.hpp"
#include "widen/common/log.hpp"

namespace widen
{
    namespace config
    {
        namespace port
        {
            int message = 10101;
        }

        void loadConfigFile(std::filesystem::path configFile)
        {
            configFile = std::filesystem::absolute(configFile);
            try
            {
                YAML::Node node = YAML::LoadFile(configFile.string());
                port::message = node["port"]["message"].as<int>();
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