#include "widen/common/proto_wrapper/identifier.hpp"

namespace widen
{
    Identifier::Identifier(const std::string &ip, const int64_t timestamp)
    {
        proto.set_allocated_ip(new std::string(ip));
        proto.set_inittimestamp(timestamp);
    }

    std::string Identifier::toString() const
    {
        return proto.DebugString();
    }

    void Identifier::deserialize(const std::string &byteString)
    {
        proto.ParseFromString(byteString);
    }

    std::string Identifier::rawSerialize() const
    {
        std::string byteString;
        proto.SerializeToString(&byteString);
        return std::move(byteString);
    }
}