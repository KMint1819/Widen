#pragma once
#include <asio.hpp>

namespace widen
{
    using asio::ip::tcp;
    class MessageListener
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

    class MessageSession : public std::enable_shared_from_this<MessageSession>
    {
        friend class MessageListener;

    public:
        MessageSession(tcp::socket socket);

    private:
        tcp::socket socket;
        std::vector<char> recvBuf;

        void start();
        void handleMessage(const std::string &);
    };
}