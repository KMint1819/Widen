#pragma once
#include "widen/common/proto_wrapper/proto_wrapper.hpp"

namespace widen
{
    class Identifier final : public ProtoWrapper
    {
    public:
        Identifier(const std::string &ip, const int64_t timestamp)
        {
            proto.set_allocated_ip(new std::string(ip));
            proto.set_inittimestamp(timestamp);
        }

        std::string toString() const override
        {
            return proto.DebugString();
        }

        void deserialize(const std::string &byteString) override
        {
            proto.ParseFromString(byteString);
        }

    protected:
        std::string rawSerialize() const override
        {
            std::string byteString;
            proto.SerializeToString(&byteString);
            return std::move(byteString);
        }

    private:
        IdentifierProto proto;
    };
}