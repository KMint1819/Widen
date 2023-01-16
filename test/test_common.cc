#include "catch.hpp"
#include "widen/common/log.hpp"
#include "widen/common/fmt.hpp"
#include "widen/common/serialization.hpp"
#include "widen/common/message_addon.hpp"

TEST_CASE("Test message addons", "[common/message_addon]")
{
    std::string s = "";
    std::string res = widen::addLengthToStringFront(s);
    int len = widen::convertLengthString(res.substr(0, 4));
    REQUIRE(len == 0);

    s = "12345";
    res = widen::addLengthToStringFront(s);
    len = widen::convertLengthString(res.substr(0, 4));
    REQUIRE(len == 5);
}

TEST_CASE("Test int64_t serialization", "[common/serialization/int64_t]")
{
    int64_t before, after;
    std::string serialized;

    //
    before = 20;
    serialized = widen::serializeNumber(before);
    after = widen::deserializeNumber<int64_t>(serialized);

    REQUIRE(before == after);

    //
    before = 10000;
    serialized = widen::serializeNumber(before);
    after = widen::deserializeNumber<int64_t>(serialized);

    REQUIRE(before == after);

    //
    before = 300000000;
    serialized = widen::serializeNumber(before);
    after = widen::deserializeNumber<int64_t>(serialized);

    REQUIRE(before == after);
}

TEST_CASE("Test uint32_t serialization", "[common/serialization/uint32_t]")
{
    uint32_t before, after;
    std::string serialized;

    //
    before = 20;
    serialized = widen::serializeNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);

    //
    before = 10000;
    serialized = widen::serializeNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);

    //
    before = 300000000;
    serialized = widen::serializeNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);
}