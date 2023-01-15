#include "catch.hpp"
#include "widen/common/log.hpp"
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