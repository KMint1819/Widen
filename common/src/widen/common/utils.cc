#include "widen/common/utils.hpp"
#include "widen/common/log.hpp"
#include "widen/common/exception.hpp"

#include <ifaddrs.h>

namespace widen
{
    int64_t getTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto nowMS = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
        auto epochMS = nowMS.time_since_epoch();
        return epochMS.count();
    }

    /// @brief A function to get self ip
    /// Reference: https://gist.github.com/quietcricket/2521037
    /// TODO: Try remove the need of this function because computers might
    /// have different network interfaces
    asio::ip::address_v4 getSelfIp(const std::string &interface)
    {
        WIDEN_TRACE("Getting ip from interface {}", interface);
#ifdef __unix__
        std::string ipAddress = "";
        ifaddrs *interfaces = nullptr;
        ifaddrs *temp_addr = nullptr;
        int success = 0;
        // retrieve the current interfaces - returns 0 on success
        success = getifaddrs(&interfaces);
        if (success == 0)
        {
            // Loop through linked list of interfaces
            temp_addr = interfaces;
            while (temp_addr != NULL)
            {
                if (temp_addr->ifa_addr->sa_family == AF_INET)
                {
                    std::string ifaName(temp_addr->ifa_name);
                    if (ifaName == interface)
                    {
                        ipAddress = inet_ntoa(((struct sockaddr_in *)temp_addr->ifa_addr)->sin_addr);
                    }
                }
                temp_addr = temp_addr->ifa_next;
            }
        }
        freeifaddrs(interfaces);
        if (ipAddress.length() == 0 || success != 0)
            throw std::logic_error(fmt::format("Failed to get self ip with interface {}", interface));
        return asio::ip::address_v4::from_string(ipAddress);
#elif defined(_WIN32)
        throw NotImplementedError("Cannot get self ip of Windows yet. Get an Unix dude...");
#endif
    }
}