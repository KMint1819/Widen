#include "widen/common/message_addon.hpp"

namespace widen
{
    std::string getDelim()
    {
        return "\r\n\r\n";
    }

    std::string addDelimToEnd(std::string s)
    {
        return s + getDelim();
    }

    std::string removeDelimFromEnd(const std::string &s)
    {
        if (s.length() < 4)
            throw std::runtime_error(fmt::format("string <{}> shorter than delimiter!", s));

        std::string delim = getDelim();
        if (!std::equal(delim.rbegin(), delim.rend(), s.rbegin()))
        {
            throw std::runtime_error(fmt::format("string <{}> does not end with a delimiter!", s));
        }

        int afterLen = s.length() - delim.length();
        return s.substr(0, afterLen);
    }
}