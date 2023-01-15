#pragma once
#include <string>
#include <utility>

#include "widen/common/fmt.hpp"

// TODO:
//     - make endianess platform-independent

namespace widen
{
    int convertLengthString(const std::string &);
    std::string addLengthToStringFront(const std::string &);
}