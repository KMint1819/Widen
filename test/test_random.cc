#include "catch.hpp"

TEST_CASE("Addings are computed", "[add]")
{
    REQUIRE(1 + 8 == 9);
    REQUIRE(18 + 19 == 37);
}