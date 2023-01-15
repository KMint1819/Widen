#include "widen/common/fmt.hpp"
#include "widen/common/log.hpp"
#include "widen/common/message_addon.hpp"

namespace widen
{
    std::string addLengthToStringFront(const std::string &s)
    {
        std::string str = fmt::format("{:04d}", s.length()) + s;
        WIDEN_TRACE("Converted <{},{}> to <{},{}>",
                    s.length(), s, str.length(), s);
        return str;
    }
    int convertLengthString(const std::string &s)
    {
        if (s.length() != 4)
            throw std::logic_error("Length string should have 4 digits!");
        int len = std::stoi(s);
        WIDEN_TRACE("Length stirng {} == int {}", s, len);
        return len;
    }
}