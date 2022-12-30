#include <asio.hpp>

#include "widen/common/log.hpp"

int main()
{
    WIDEN_INFO("Hello WIDEN worker!");

    asio::io_context ioc;
}