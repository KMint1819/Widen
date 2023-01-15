#include "widen/common/log.hpp"
#include "widen/common/message_addon.hpp"
#include "widen/messages.pb.h"
#include "widen/node/message_listener.hpp"
#include "widen/node/handlers/joinRequestHandler.hpp"

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
        doReadHeader();
    }

    void MessageSession::doReadHeader()
    {
        auto self(shared_from_this());
        asio::async_read(socket, asio::buffer(recvBuf, 4),
                         [this, self](asio::error_code ec, std::size_t sz)
                         {
                             if (ec)
                             {
                                 WIDEN_ERROR("Error read header: {}", ec.message());
                             }
                             else
                             {
                                 WIDEN_TRACE("Read {} bytes of header", sz);

                                 int bodyLength = widen::convertLengthString(std::string(recvBuf.begin(), recvBuf.begin() + sz));
                                 doReadBody(bodyLength);
                             }
                         });
    }

    void MessageSession::doReadBody(int length)
    {
        auto self(shared_from_this());
        asio::async_read(socket, asio::buffer(recvBuf, length),
                         [this, self](asio::error_code ec, std::size_t sz)
                         {
                             if (ec)
                             {
                                 WIDEN_ERROR("Error read body: {}", ec.message());
                             }
                             else
                             {
                                 WIDEN_TRACE("Read {} bytes of body", sz);
                                 handleMessage(std::string(recvBuf.begin(), recvBuf.begin() + sz));
                             }
                             doReadHeader();
                         });
    }

    void MessageSession::handleMessage(const std::string &msg)
    {
        Message message;
        message.ParseFromString(msg);
        WIDEN_TRACE("Handling message: {}", message.DebugString());

        if (message.has_joinrequest())
        {
            WIDEN_TRACE("Message is a join request!");
            std::make_shared<JoinRequestHandler>(std::move(socket), message.joinrequest())->start();
        }
    }
}