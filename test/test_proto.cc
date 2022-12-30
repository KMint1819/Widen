#include "catch.hpp"

#include <cstdio>

#include <google/protobuf/any.h>

#include "widen/gossip.pb.h"

TEST_CASE("Protobuf playground", "[protobuf-play]")
{
    widen::GossipNewMember gossip;
    gossip.set_id(1819);
    printf("Gossip: %s\n", gossip.DebugString().c_str());
}