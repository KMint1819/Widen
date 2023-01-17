#pragma once

#include <string>
#include <utility>

#include "widen/common/log.hpp"
#include "widen/common/serialization.hpp"
#include "widen/messages.pb.h"

namespace widen
{
    /**
     * @brief Base wrapper class that every protobuf file should have one
     * wrapper class inherit to this
     *
     */
    class ProtoWrapper
    {
    public:
        virtual std::string toString() const = 0;

        /**
         * @brief Serialize ProtoWrapper to length string + body string
         *
         * @return length string + body string
         */
        virtual std::string serialize() const;

        /**
         * @brief Deserialize the ***body*** string to the children class
         *
         */
        virtual void deserialize(const std::string &) = 0;
        virtual ~ProtoWrapper(){};

    protected:
        virtual std::string rawSerialize() const = 0;
    };
}