#include "widen/common/log.hpp"
#include "widen/common/message_addon.hpp"
#include "widen/messages.pb.h"
#include "widen/worker/message_listener.hpp"
#include "widen/worker/handlers/joinRequestHandler.hpp"

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
                WIDEN_ERROR("Error accept: {}", ec.message());
            }
            else
            {
                std::make_shared<MessageSession>(std::move(socket))->start();
            } 
            doAccept(); });
    }

    MessageSession::MessageSession(tcp::socket socket)
        : socket(std::move(socket)),
          recvBuf(recvBufSize) {}

    void MessageSession::start()
    {
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
                                       std::string msgWithDelim(recvBuf.begin(), recvBuf.begin() + sz);
                                       std::string msg = removeDelimFromEnd(msgWithDelim);
                                       handleMessage(msg);
                                   }
                               });
    }

    void MessageSession::handleMessage(const std::string &msg)
    {
        Message message;
        message.ParseFromString(msg);

        if (message.has_joinrequest())
        {
            std::make_shared<JoinRequestHandler>(std::move(socket), message.joinrequest())->start();
        }
    }
}