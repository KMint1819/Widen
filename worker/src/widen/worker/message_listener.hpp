#pragma once
#include <asio.hpp>

namespace widen
{
    using asio::ip::tcp;
    class MessageListener : std::enable_shared_from_this<MessageListener>
    {
    public:
        MessageListener(asio::io_context &ioc, int port);
        void start();

    private:
        asio::io_context &ioc;
        tcp::acceptor acceptor;
        tcp::socket socket;
        int port;

        void doAccept();
    };

    class MessageSession
    {
        friend class MessageListener;

    public:
        MessageSession(tcp::socket socket);

    private:
        tcp::socket socket;
        const int recvBufSize = 1024;
        std::vector<char> recvBuf;

        void start();
        void handleMessage(const std::string &);
    };
}