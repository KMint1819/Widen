#include "catch.hpp"

#include <cstdio>

#include <google/protobuf/any.h>

// TEST_CASE("Protobuf playground", "[protobuf-play]")
// {
//     // widen::GossipNewMember gossip;
//     // gossip.set_id(1819);
//     // printf("Gossip: %s\n", gossip.DebugString().c_str());
// }

// TEST_CASE("JoinRequest proto wrapper", "[proto_wrapper/JoinRequest]")
// {
//     const std::string ip = "123.456.789.101";
//     const int64_t timestamp = 1000000L;
//     widen::JoinRequest req({ip, timestamp});

//     std::string serialized = req.serialize();
//     std::string lengthString = serialized.substr(0, 4);
//     uint32_t bodyLength = widen::deserializeNumber<uint32_t>(lengthString);
//     REQUIRE(bodyLength == serialized.length() - 4);

//     auto receivedReq = widen::JoinRequest::buildDeserialize(serialized.substr(4));
//     REQUIRE(receivedReq.getIdentifier().getIp() == ip);
//     REQUIRE(receivedReq.getIdentifier().getInitTimestamp() == timestamp);
// }