#pragma once

#include "widen/common/proto_wrapper/proto_message.hpp"

namespace widen
{
    std::string ProtoMessage::serialize() const
    {
        std::string body = rawSerialize();
        std::string lengthString = serialize4BytesNumber(body.length());

        return lengthString + body;
    }
}