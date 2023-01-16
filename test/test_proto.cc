#include "catch.hpp"

#include <cstdio>

#include <google/protobuf/any.h>

#include "widen/common/proto_wrapper/identifier.hpp"
#include "widen/gossip.pb.h"

TEST_CASE("Protobuf playground", "[protobuf-play]")
{
    // widen::GossipNewMember gossip;
    // gossip.set_id(1819);
    // printf("Gossip: %s\n", gossip.DebugString().c_str());
}

TEST_CASE("identifier proto wrapper", "[proto_wrapper/identifier]")
{
    widen::Identifier identifier("123.234.456.189", 1000000000L);
    std::string serialized = identifier.serialize();
    std::string lengthString = serialized.substr(0, 4);
    uint32_t bodyLength = widen::deserializeNumber<uint32_t>(lengthString);
    REQUIRE(bodyLength == serialized.length() - 4);
}