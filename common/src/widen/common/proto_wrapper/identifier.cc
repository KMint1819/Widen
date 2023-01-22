#include "widen/common/proto_wrapper/identifier.hpp"

namespace widen
{
    Identifier::Identifier() {}

    Identifier::Identifier(const std::string &ip, const int64_t timestamp)
    {
        setIp(ip);
        setInitTimestamp(timestamp);
    }

    Identifier::Identifier(const Proto &proto)
    {
        setIp(proto.ip());
        setInitTimestamp(proto.init_timestamp());
    }

    Identifier::Proto Identifier::getProto() const
    {
        return proto;
    }

    std::string Identifier::getIp() const
    {
        return proto.ip();
    }

    void Identifier::setIp(const std::string &ip)
    {
        proto.set_ip(ip);
    }

    int64_t Identifier::getInitTimestamp() const
    {
        return proto.init_timestamp();
    }

    void Identifier::setInitTimestamp(const int64_t timestamp)
    {
        proto.set_init_timestamp(timestamp);
    }

    std::string Identifier::toString() const
    {
        return proto.DebugString();
    }
}