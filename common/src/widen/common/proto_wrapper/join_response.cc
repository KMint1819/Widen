#include "widen/common/proto_wrapper/join_response.hpp"

namespace widen
{
    JoinResponse::JoinResponse()
    {
    }
    JoinResponse::JoinResponse(const Proto &proto)
        : proto(proto)
    {
    }
    JoinResponse::JoinResponse(const std::string &ip, const std::vector<Identifier> &identifiers)
        : identifiers(identifiers)
    {
        proto.clear_identifiers();
        for (const auto &identifier : identifiers)
        {
            Identifier::Proto *data = proto.add_identifiers();
            data->set_ip(identifier.getIp());
            data->set_init_timestamp(identifier.getInitTimestamp());
        }
        proto.set_requester_ip(ip);
    }

    JoinResponse JoinResponse::buildDeserialize(const std::string &serialized)
    {
        JoinResponse res;
        res.deserialize(serialized);
        return std::move(res);
    }

    std::string JoinResponse::getRequesterIp() const
    {
        return proto.requester_ip();
    }

    std::vector<Identifier> JoinResponse::getIdentifiers() const
    {
        return {proto.identifiers().begin(), proto.identifiers().end()};
    }

    std::string JoinResponse::toString() const
    {
        return proto.DebugString();
    }

    std::string JoinResponse::rawSerialize() const
    {
        std::string tmp;
        proto.SerializeToString(&tmp);
        return std::move(tmp);
    }

    void JoinResponse::deserialize(const std::string &serialized)
    {
        proto.ParseFromString(serialized);
        identifiers = {proto.identifiers().begin(), proto.identifiers().end()};
    }
}