#pragma once

#include <stdexcept>

namespace widen
{
    class NotImplementedError : public std::logic_error
    {
    public:
        NotImplementedError();
    };
}