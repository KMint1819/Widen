#include "widen/common/proto_wrapper/join_request.hpp"

namespace widen
{

    JoinRequest::JoinRequest(){};

    JoinRequest::JoinRequest(const int64_t initTimestamp)
    {
        proto.set_init_timestamp(initTimestamp);
    }

    JoinRequest JoinRequest::buildDeserialize(const std::string &serialized)
    {
        JoinRequest req;
        req.deserialize(serialized);
        return std::move(req);
    }

    int64_t JoinRequest::getInitTimestamp() const
    {
        return proto.init_timestamp();
    }

    std::string JoinRequest::toString() const
    {
        return proto.DebugString();
    }

    void JoinRequest::deserialize(const std::string &serialized)
    {
        proto.ParseFromString(serialized);
    }

    std::string JoinRequest::rawSerialize() const
    {
        std::string serialized;
        proto.SerializeToString(&serialized);
        return std::move(serialized);
    }
}