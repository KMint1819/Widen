#pragma once
#include <asio.hpp>

#include "widen/common/proto_wrapper/join_request.hpp";
#include "widen/common/proto_wrapper/join_response.hpp";

namespace widen
{
    using asio::ip::tcp;
    class Introducer
    {
        using IpChangeCallback = std::function<void(asio::ip::address_v4)>;
        using Request = JoinRequest;

    public:
        Introducer(asio::io_context &ioc, int port);
        Introducer(asio::io_context &ioc, int port, IpChangeCallback onIpChange);
        void start();

    private:
        asio::io_context &ioc;
        tcp::acceptor acceptor;
        tcp::socket socket;
        int port;
        std::optional<IpChangeCallback> onIpChange;

        void doAccept();

        class Session : public std::enable_shared_from_this<Session>
        {
        public:
            Session(tcp::socket socket);
            void start();

        private:
            tcp::socket socket;
            std::array<char, 8192> recvBuf;

            void doRead();
            void handleMessage(const std::string &);
        };
    };
}