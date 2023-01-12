#include <yaml-cpp/yaml.h>

#include "widen/common/config.hpp"
#include "widen/common/log.hpp"

namespace widen
{
    long getTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto nowMS = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epochMS = nowMS.time_since_epoch();
        return epochMS.count();
    }
}