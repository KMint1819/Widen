#include "widen/common/proto_wrapper/proto_wrapper.hpp"

namespace widen
{
    std::string ProtoWrapper::serialize() const
    {
        std::string body = rawSerialize();
        uint32_t bodyLength = body.length();
        std::string header = serializeNumber(bodyLength);
        return header + body;
    }
}