#include "catch.hpp"
#include "widen/common/log.hpp"

TEST_CASE("Logging playground", "[logs]")
{
}
TEST_CASE("Addings are computed", "[add]")
{
    REQUIRE(1 + 8 == 9);
    REQUIRE(18 + 19 == 37);
}