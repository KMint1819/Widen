#include "alan/log.hpp"
#include "alan/lib.hpp"

namespace alan
{
    int add(int a, int b)
    {
        ALAN_TRACE("Adding {} and {}", a, b);
        return a + b;
    }
}