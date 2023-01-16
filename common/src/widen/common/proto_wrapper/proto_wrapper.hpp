#pragma once

#include <string>
#include <utility>

#include "widen/common/log.hpp"
#include "widen/common/serialization.hpp"
#include "widen/messages.pb.h"

namespace widen
{
    class ProtoWrapper
    {
    public:
        virtual std::string toString() const = 0;

        /**
         * @brief Serialize ProtoWrapper to length string + body string
         *
         * @return std::pair<std::string, std::string>
         */
        virtual std::string serialize() const
        {
            std::string body = rawSerialize();
            uint32_t bodyLength = body.length();
            std::string header = serializeNumber(bodyLength);
            return header + body;
        }

        /**
         * @brief Deserialize the ***body*** to the children class
         *
         */
        virtual void deserialize(const std::string &) = 0;
        virtual ~ProtoWrapper(){};

    protected:
        virtual std::string rawSerialize() const = 0;
    };
}