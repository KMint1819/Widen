#include "catch.hpp"
#include "widen/common/log.hpp"
#include "widen/common/message_addon.hpp"

TEST_CASE("Test message addons", "[common/message_addon]")
{
    std::string s = "";
    REQUIRE_THROWS(widen::removeDelimFromEnd(s));

    s = "some Message";
    REQUIRE_THROWS(widen::removeDelimFromEnd(s));

    std::string added = widen::addDelimToEnd(s);
    REQUIRE(s.length() + widen::getMessageDelim().length() == added.length());

    std::string removed = widen::removeDelimFromEnd(added);
    REQUIRE(removed == s);
}