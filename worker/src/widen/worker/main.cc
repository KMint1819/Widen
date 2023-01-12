#include <asio.hpp>

#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/worker/worker.hpp"

int main(int argc, char **argv)
{
    widen::config::loadConfigFile("config.yaml");
    WIDEN_INFO("After config: port = {}", widen::config::port::message);

    widen::Worker worker(argc, argv);
    worker.start();

    return 0;
}