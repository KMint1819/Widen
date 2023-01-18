#pragma once
#include <string>

namespace widen
{
    class ProtoWrapper
    {
    public:
        virtual std::string toString() const = 0;
        virtual ~ProtoWrapper() {}
    };
}