#pragma once

#include "widen/common/proto_wrapper/proto_message.hpp"
#include "widen/common/proto_wrapper/identifier.hpp"
#include "widen/introducer.pb.h"

namespace widen
{
    class JoinResponse final : public ProtoMessage
    {
        using Proto = proto::introducer::JoinResponseProto;

    public:
        JoinResponse();
        JoinResponse(const Proto &);
        JoinResponse(const std::string &ip,
                     const std::vector<Identifier> &identifiers);
        static JoinResponse buildDeserialize(const std::string &);

        std::string getRequesterIp() const;
        std::vector<Identifier> getIdentifiers() const;

        std::string toString() const override;
        std::string rawSerialize() const override;

    private:
        Proto proto;
        std::vector<Identifier> identifiers;
        void deserialize(const std::string &);
    };
}