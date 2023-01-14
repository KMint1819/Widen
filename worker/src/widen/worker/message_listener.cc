#include "widen/common/log.hpp"
#include "widen/common/message_addon.hpp"
#include "widen/messages.pb.h"
#include "widen/worker/message_listener.hpp"
#include "widen/worker/handlers/joinRequestHandler.hpp"

namespace widen
{
    MessageListener::MessageListener(asio::io_context &ioc, int port)
        : ioc(ioc),
          acceptor(ioc, tcp::endpoint(tcp::v4(), port)),
          socket(ioc),
          port(port)
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
                WIDEN_ERROR("Error accept: {}", ec.message());
            }
            else
            {
                WIDEN_TRACE("Accepting: {}", socket.remote_endpoint().address().to_string());
                std::make_shared<MessageSession>(std::move(socket))->start();
            } 
            doAccept(); });
    }

    MessageSession::MessageSession(tcp::socket socket)
        : socket(std::move(socket))
    {
    }

    void MessageSession::start()
    {
        auto self(shared_from_this());
        WIDEN_TRACE("Reading message from {}...", socket.remote_endpoint().address().to_string());
        asio::async_read_until(socket,
                               asio::dynamic_buffer(recvBuf),
                               getMessageDelim(),
                               [this](asio::error_code ec, std::size_t sz)
                               {
                                   if (ec)
                                   {
                                       WIDEN_ERROR("Error read: {}", ec.message());
                                   }
                                   else
                                   {
                                       WIDEN_TRACE("Read {} bytes including delim", sz);
                                       std::string msg(recvBuf.begin(), recvBuf.begin() + sz);
                                       msg = removeDelimFromEnd(msg);
                                       handleMessage(msg);
                                   }
                               });
    }

    void MessageSession::handleMessage(const std::string &msg)
    {
        Message message;
        message.ParseFromString(msg);
        message.PrintDebugString();
        // WIDEN_TRACE("Handling message: {}", message.PrintDebugString());

        if (message.has_joinrequest())
        {
            WIDEN_TRACE("Message is a join request!");
            std::make_shared<JoinRequestHandler>(std::move(socket), message.joinrequest())->start();
        }
    }
}