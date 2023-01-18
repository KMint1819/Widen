#include "widen/common/proto_wrapper/join_request.hpp"

namespace widen
{

    JoinRequest::JoinRequest(const Identifier &identifier)
        : identifier(identifier)
    {
        proto.set_allocated_identifier(new Identifier::Proto(identifier.getProto()));
    }

    Identifier JoinRequest::getIdentifier() const
    {
        return identifier;
    }

    std::string JoinRequest::toString() const
    {
        return proto.DebugString();
    }

    void JoinRequest::deserialize(const std::string &serialized)
    {
        proto.ParseFromString(serialized);
        identifier = Identifier(proto.identifier());
    }

    std::string JoinRequest::rawSerialize() const
    {
        std::string serialized;
        proto.SerializeToString(&serialized);
        return std::move(serialized);
    }
}