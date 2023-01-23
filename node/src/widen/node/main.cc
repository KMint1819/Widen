#include <asio.hpp>

#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/node/node.hpp"

int main(int argc, char **argv)
{
    widen::config::loadConfigFile("config.yaml");
    WIDEN_INFO("After config: introducer port = {}", widen::config::port::introducer);
    widen::Node node(argc, argv);
    node.start();

    return 0;
}