#include "catch.hpp"

#include <cstdio>

#include <google/protobuf/any.h>

#include "widen/common/proto_wrapper/join_request.hpp"

// TEST_CASE("Protobuf playground", "[protobuf-play]")
// {
//     // widen::GossipNewMember gossip;
//     // gossip.set_id(1819);
//     // printf("Gossip: %s\n", gossip.DebugString().c_str());
// }

TEST_CASE("JoinRequest proto wrapper", "[proto_wrapper/JoinRequest]")
{
    const std::string ip = "123.456.789.101";
    const int64_t timestamp = 1000000L;
    widen::JoinRequest req({ip, timestamp});
    printf("REQ: \n%s\n", req.toString().c_str());
    std::string serialized = req.serialize();
    printf("SERI: %s\n", serialized.c_str());
    printf("LEN: %d\n", serialized.length());
    std::string lengthString = serialized.substr(0, 4);
    uint32_t bodyLength = widen::deserializeNumber<uint32_t>(lengthString);
    // REQUIRE(bodyLength == serialized.length() - 4);

    widen::JoinRequest receivedReq({"wrong ip", 87878787});
    printf("Before: \n%s\n", receivedReq.toString().c_str());
    receivedReq.deserialize(serialized.substr(12));
    printf("After: \n%s\n", receivedReq.toString().c_str());

    REQUIRE(receivedReq.getIdentifier().getIp() == ip);
    REQUIRE(receivedReq.getIdentifier().getInitTimestamp() == timestamp);
}