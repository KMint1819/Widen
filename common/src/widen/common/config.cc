#include <yaml-cpp/yaml.h>

#include "widen/common/config.hpp"
#include "widen/common/log.hpp"

namespace widen
{
    namespace config
    {
        namespace port
        {
            int introducer = 10101;
            int failureDetection = 10102;
            int distributedFS = 10103;
        }

        void loadConfigFile(std::filesystem::path configFile)
        {
            configFile = std::filesystem::absolute(configFile);
            try
            {
                YAML::Node node = YAML::LoadFile(configFile.string());
                port::introducer = node["port"]["introducer"].as<int>();
                port::failureDetection = node["port"]["failure_detection"].as<int>();
                port::distributedFS = node["port"]["distributed_fs"].as<int>();
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