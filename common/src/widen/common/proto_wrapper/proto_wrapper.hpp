#pragma once
#include <string>

namespace widen
{
    /**
     * @brief Base class for all protobuf wrapper.
     *
     */
    class ProtoWrapper
    {
    public:
        virtual std::string toString() const = 0;
        virtual ~ProtoWrapper() {}
    };
}