#pragma once

#include "widen/common/config.hpp"
#include <asio.hpp>

namespace widen
{
    using asio::ip::tcp;

    /// TODO: abstract shared functions to parent class
    /// @brief
    /// Workflow: readHeaderLen -> readHeader -> readBody ---]
    ///             ^                                        |
    ///             |                                        |
    ///             [--------------<---------<---------------]

    class Introducer
    {
    public:
        Introducer(asio::io_context &ioc, int port = config::port::introducer);
        void start();

    private:
        asio::io_context &ioc;
        tcp::acceptor acceptor;
        tcp::socket socket;
        int port;

        void doAccept();

        class Session : public std::enable_shared_from_this<Session>
        {
        public:
            Session(tcp::socket socket);
            void start();

        private:
            tcp::socket socket;
            std::array<char, 8192> recvBuf;

            void doReadHeaderLen();
            void doReadHeader(uint32_t headerLen);
            void doReadBody(const std::string &type, uint32_t bodyLen);
            void handleBody(const std::string &type, const std::string &body);
        };
    };
}