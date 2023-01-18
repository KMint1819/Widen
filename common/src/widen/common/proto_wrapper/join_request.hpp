#pragma once
#include "widen/common/proto_wrapper/protomsg_wrapper.hpp"
#include "widen/common/proto_wrapper/identifier.hpp"
#include "widen/introducer.pb.h"

namespace widen
{
    class JoinRequest final : public ProtomsgWrapper
    {
        using Proto = proto::introducer::JoinRequestProto;

    public:
        JoinRequest(const Identifier &);
        Identifier getIdentifier() const;
        std::string toString() const override;
        void deserialize(const std::string &);
        std::string rawSerialize() const;

        inline std::string getType() const override { return "JOIN"; }

    private:
        Proto proto;
        Identifier identifier;
    };
}