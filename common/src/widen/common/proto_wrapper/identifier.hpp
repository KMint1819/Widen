#pragma once
#include "widen/common/proto_wrapper/proto_wrapper.hpp"

namespace widen
{
    class Identifier final : public ProtoWrapper
    {
    public:
        Identifier(const std::string &ip, const int64_t timestamp);

        std::string toString() const override;

        void deserialize(const std::string &byteString) override;

        std::string ip() const;

        int64_t inittimestamp() const;

    protected:
        std::string rawSerialize() const override;

    private:
        proto::IdentifierProto proto;
    };
}