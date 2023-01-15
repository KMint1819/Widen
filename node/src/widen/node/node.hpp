#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <asio.hpp>

#include "widen/messages.pb.h"

namespace widen
{
    using asio::ip::tcp;

    class Node
    {
    public:
        Node(int argc, char **argv);
        void start();

    private:
        asio::io_context ioc;
        tcp::resolver::results_type introducerEndpoints;

        std::vector<Identifier> joinViaIntroducer();
        void mainLoop();
    };
}