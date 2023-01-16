#include "widen/common/proto_wrapper/join_request.hpp"

namespace widen
{
    JoinRequest::JoinRequest(const std::string &ip, const int64_t timestamp)
        : identifier(ip, timestamp)
    {
    }

    JoinRequest::JoinRequest(const Identifier &identifier)
        : identifier(identifier)
    {
    }

    std::string JoinRequest::toString() const {}

    void JoinRequest::deserialize(const std::string &byteString)
    {
    }

    std::string JoinRequest::rawSerialize() const
    {
    }
}