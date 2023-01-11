#include "widen/common/log.hpp"
#include "widen/worker/message_listener.hpp"
#include "widen/introduce.pb.h"

namespace widen
{
    MessageListener::MessageListener(asio::io_context &ioc, int port)
        : ioc(ioc),
          port(port),
          acceptor(ioc, tcp::endpoint(tcp::v4(), port)),
          socket(ioc)
    {
    }

    void MessageListener::start()
    {
        doAccept();
    }

    void MessageListener::doAccept()
    {
        acceptor.async_accept(socket, [this](asio::error_code ec)
                              {
            if(ec)
            {
                WIDEN_ERROR("Error accepting: {}", ec.message());
            }
            else
            {
                std::make_shared<MessageSession>(std::move(socket))->start();
            } 
            doAccept(); });
    }

    MessageSession::MessageSession(tcp::socket socket)
        : socket(std::move(socket)) {}

    void MessageSession::start()
    {
    }
}