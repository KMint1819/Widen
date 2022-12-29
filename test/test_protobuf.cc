#include "catch.hpp"

#include <cstdio>

#include <google/protobuf/any.h>

#include "me.pb.h"

TEST_CASE("Protobuf playground", "[protobuf-play]")
{
    widen::test::Me me;
    me.set_name("Vincent");
    me.set_groupid(50);
    printf("Me: %s\n", me.DebugString().c_str());
}