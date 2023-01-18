#include "catch.hpp"
#include "widen/common/log.hpp"
#include "widen/common/fmt.hpp"
#include "widen/common/serialization.hpp"

TEST_CASE("Test int64_t serialization", "[common/serialization/int64_t]")
{
    uint32_t before, after;
    std::string serialized;

    //
    before = 20;
    serialized = widen::serialize4BytesNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);

    //
    before = 10000;
    serialized = widen::serialize4BytesNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);

    //
    before = 300000000;
    serialized = widen::serialize4BytesNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);
}

TEST_CASE("Test uint32_t serialization", "[common/serialization/uint32_t]")
{
    uint32_t before, after;
    std::string serialized;

    //
    before = 20;
    serialized = widen::serialize4BytesNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);

    //
    before = 10000;
    serialized = widen::serialize4BytesNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);

    //
    before = 300000000;
    serialized = widen::serialize4BytesNumber(before);
    after = widen::deserializeNumber<uint32_t>(serialized);

    REQUIRE(before == after);
}