#pragma once
#include "widen/common/proto_wrapper/proto_message.hpp"
#include "widen/common/proto_wrapper/identifier.hpp"
#include "widen/introducer.pb.h"

namespace widen
{
    class JoinRequest final : public ProtoMessage
    {
        using Proto = proto::introducer::JoinRequestProto;

    public:
        JoinRequest();
        JoinRequest(const Proto &);
        JoinRequest(const int64_t initTimestamp);
        static JoinRequest buildDeserialize(const std::string &);

        int64_t getInitTimestamp() const;

        std::string toString() const override;
        std::string rawSerialize() const override;

    private:
        Proto proto;
        void deserialize(const std::string &);
    };
}