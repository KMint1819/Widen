#include <asio.hpp>

#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/worker/worker.hpp"

int main()
{
    widen::config::loadConfigFile("config.yaml");
    WIDEN_INFO("After config: port = {}", widen::config::port::join);
    widen::Worker worker;
    worker.start();

    return 0;
}