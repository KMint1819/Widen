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
     * wrapper class inherited from this. All subclass must also implement
     * their own static deserialize function.
     *
     */
    class ProtoMessage : public ProtoWrapper
    {
    public:
        
        /**
         * @brief Serialize ProtoWrapper to length string + body string
         *
         * @return length string + body string
         */
        virtual std::string serialize() const;

        virtual std::string toString() const override = 0;

        virtual ~ProtoMessage(){};

    protected:
        virtual std::string rawSerialize() const = 0;
    };
}