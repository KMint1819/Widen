#include <cstdio>
#include <chrono>
#include <vector>

#include "widen/log.hpp"

int main()
{
    std::string someMessage = "Merry Christmas!";
    WIDEN_TRACE("Hello WIDEN and wish you {}", someMessage);

    WIDEN_INFO("I'd rather be {1} than {0}.", "right", "happy");

    using namespace std::literals::chrono_literals;
    WIDEN_WARN("Default format: {} {}", 42s, 100ms);
    WIDEN_WARN("strftime-like format: {:%H:%M:%S}", 3h + 15min + 30s);

    std::vector<int> v = {1, 2, 3};
    WIDEN_ERROR("printing vector! {}", v);
    return 0;
}