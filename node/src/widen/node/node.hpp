#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <asio.hpp>

#include "widen/node/memberlist.hpp"
#include "widen/common/proto_wrapper/join_request.hpp"

namespace widen
{
    class Node
    {

        using address_v4 = asio::ip::address_v4;
        using tcp = asio::ip::tcp;

    public:
        Node(int argc, char **argv);
        void start();

    private:
        asio::io_context ioc;
        tcp::resolver::results_type introducerEndpoints;
        address_v4 selfAddr;

        Memberlist joinViaIntroducer();
    };
}