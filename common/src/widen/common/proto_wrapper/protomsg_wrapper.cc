#pragma once

#include "widen/common/proto_wrapper/protomsg_wrapper.hpp"

namespace widen
{
    std::string ProtomsgWrapper::serialize() const
    {
        std::string body = rawSerialize();
        uint32_t bodyLength = body.length();

        proto::general::HeaderProto header;
        header.set_body_length(bodyLength);
        header.set_type(getType());

        std::string headerString;
        header.SerializeToString(&headerString);
        std::string headerLengthString = serialize4BytesNumber(headerString.length());

        return headerLengthString + headerString + body;
    }

    Header::Header(const std::string &headerString)
    {
        proto.ParseFromString(headerString);
    }

    std::string Header::getType() const
    {
        return proto.type();
    }

    uint32_t Header::getBodyLength() const
    {
        return proto.body_length();
    }

    std::string Header::toString() const
    {
        return proto.DebugString();
    }
}