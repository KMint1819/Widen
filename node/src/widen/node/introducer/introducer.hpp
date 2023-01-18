#pragma once
#include <asio.hpp>

namespace widen
{
    using asio::ip::tcp;
    class Introducer
    {
    public:
        Introducer(asio::io_context &ioc, int port);
        void start();

    private:
        asio::io_context &ioc;
        tcp::acceptor acceptor;
        tcp::socket socket;
        int port;

        void doAccept();
    };

    // class MessageSession : public std::enable_shared_from_this<MessageSession>
    // {
    // public:
    //     MessageSession(tcp::socket socket);
    //     void start();

    // private:
    //     tcp::socket socket;
    //     std::array<char, 8192> recvBuf;

    //     void doReadHeader();
    //     void doReadBody(int);
    //     void handleMessage(const std::string &);
    // };
}