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
        JoinRequest(const Identifier &);
        static JoinRequest buildDeserialize(const std::string &);

        Identifier getIdentifier() const;

        std::string toString() const override;
        std::string rawSerialize() const override;

    private:
        Proto proto;
        Identifier identifier;
        void deserialize(const std::string &);
    };
}