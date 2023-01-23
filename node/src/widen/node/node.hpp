#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <asio.hpp>

#include "widen/node/memberlist.hpp"

namespace widen
{
    class Node
    {
        using tcp = asio::ip::tcp;

    public:
        Node(int argc, char **argv);
        void start();

    private:
        asio::io_context ioc;
        tcp::resolver::results_type introducerEndpoints;

        Memberlist joinViaIntroducer();
    };
}