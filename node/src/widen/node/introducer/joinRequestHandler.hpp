#pragma once
#include <asio.hpp>
#include "widen/general.pb.h"
#include "widen/introducer.pb.h"

namespace widen
{
    using asio::ip::tcp;
    class JoinRequestHandler : public std::enable_shared_from_this<JoinRequestHandler>
    {
        using Req = proto::JoinRequest;
        using Res = proto::JoinResponse;

    public:
        JoinRequestHandler(tcp::socket, const std::string &body);
        void start();

    private:
        tcp::socket socket;
        Req req;
    };
}