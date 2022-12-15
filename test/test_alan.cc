#include "alan/lib.hpp"
#include "catch.hpp"

TEST_CASE("Addings are computed", "[add]")
{
    REQUIRE(alan::add(1, 8) == 9);
    REQUIRE(alan::add(18, 19) == 37);
}