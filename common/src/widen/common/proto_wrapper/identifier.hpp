#pragma once
#include <string>

#include "widen/identifier.pb.h"
#include "widen/common/proto_wrapper/proto_wrapper.hpp"

namespace widen
{
    class Identifier final : public ProtoWrapper
    {
    public:
        using Proto = proto::IdentifierProto;
        Identifier();
        Identifier(const Proto &);
        Identifier(const std::string &ip, const int64_t timestamp);

        Proto getProto() const;

        std::string getIp() const;

        void setIp(const std::string &);

        int64_t getInitTimestamp() const;

        void setInitTimestamp(const int64_t);

        std::string toString() const override;

    private:
        Proto proto;
    };
}