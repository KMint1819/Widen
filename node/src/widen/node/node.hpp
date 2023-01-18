#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <asio.hpp>

#include "widen/node/memberlist.hpp"
#include "widen/common/proto_wrapper/join_request.hpp"

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

        Memberlist joinViaIntroducer();
        JoinRequest constructJoinRequest(std::string ip, long timestamp);
    };
}