#pragma once
#include <asio.hpp>
#include "widen/general.pb.h"
#include "widen/introducer.pb.h"

namespace widen
{
    class JoinRequestHandler : public std::enable_shared_from_this<JoinRequestHandler>
    {
        using tcp = asio::ip::tcp;
        using Req = proto::JoinRequest;
        using Res = proto::JoinResponse;

    public:
        JoinRequestHandler(tcp::socket, const std::string &body);
        void start();
        void doWrite();

    private:
        tcp::socket socket;
        Req req;
    };
}