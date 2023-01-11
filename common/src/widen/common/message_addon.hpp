#pragma once
#include <iostream>

#include "widen/common/fmt.hpp"

namespace widen
{
    std::string getDelim();

    std::string addDelimToEnd(std::string s);

    std::string removeDelimFromEnd(const std::string &s);
}