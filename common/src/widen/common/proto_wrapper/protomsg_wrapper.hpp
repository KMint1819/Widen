#pragma once

#include <string>
#include <utility>

#include "widen/common/log.hpp"
#include "widen/common/serialization.hpp"
#include "widen/common/proto_wrapper/proto_wrapper.hpp"

#include "widen/general.pb.h"

namespace widen
{
    /**
     * @brief Base wrapper class that every protobuf message should have one
     * wrapper class inherited from this
     *
     */
    class ProtomsgWrapper : public ProtoWrapper
    {
    public:
        /**
         * @brief Serialize ProtoWrapper to length string + body string
         *
         * @return header length string + header string + body string
         */
        virtual std::string serialize() const
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

        virtual std::string getType() const = 0;

        /**
         * @brief Deserialize the ***body*** string to the children class
         *
         */
        virtual void deserialize(const std::string &) = 0;

        virtual std::string toString() const override = 0;

        virtual ~ProtomsgWrapper(){};

    protected:
        virtual std::string rawSerialize() const = 0;
    };

    class Header final : public ProtoWrapper
    {
        using Proto = proto::general::HeaderProto;

    public:
        Header(const std::string &);
        std::string getType() const;
        uint32_t getBodyLength() const;
        std::string toString() const override;

    private:
        Proto proto;
    };
}