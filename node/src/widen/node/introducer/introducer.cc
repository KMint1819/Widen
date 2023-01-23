#include "widen/common/log.hpp"
#include "widen/common/serialization.hpp"
#include "widen/node/introducer/introducer.hpp"
#include "widen/general.pb.h"
#include "widen/introducer.pb.h"
#include "widen/node/introducer/joinRequestHandler.hpp"

namespace widen
{
    Introducer::Introducer(asio::io_context &ioc, int port)
        : ioc(ioc),
          acceptor(ioc, tcp::endpoint(tcp::v4(), port)),
          socket(ioc),
          port(port)
    {
    }

    void Introducer::start()
    {
        doAccept();
    }

    void Introducer::doAccept()
    {
        acceptor.async_accept(socket, [this](asio::error_code ec)
                              {
            if(ec)
                WIDEN_ERROR("Error accept: {}", ec.message());
            else
            {
                WIDEN_TRACE("Accepting: {}", socket.remote_endpoint().address().to_string());
                std::make_shared<Session>(std::move(socket))->start();
            }
            doAccept(); });
    }

    Introducer::Session::Session(tcp::socket socket)
        : socket(std::move(socket))
    {
    }

    void Introducer::Session::start()
    {
        doReadHeaderLen();
    }

    void Introducer::Session::doReadHeaderLen()
    {
        auto self(shared_from_this());
        asio::async_read(socket, asio::buffer(recvBuf, 4),
                         [this, self](asio::error_code ec, std::size_t sz)
                         {
                             if (ec)
                             {
                                 WIDEN_ERROR("Error read header length: {}", ec.message());
                             }
                             else
                             {
                                 WIDEN_TRACE("Read {} bytes of header length", sz);

                                 int bodyLength = deserializeNumber<uint32_t>(std::string(recvBuf.begin(), recvBuf.begin() + sz));
                                 doReadHeader(bodyLength);
                             }
                         });
    }
    void Introducer::Session::doReadHeader(std::uint32_t headerLen)
    {
        auto self(shared_from_this());
        asio::async_read(socket, asio::buffer(recvBuf, headerLen),
                         [this, self](asio::error_code ec, std::size_t sz)
                         {
                             if (ec)
                             {
                                 WIDEN_ERROR("Error read header: {}", ec.message());
                             }
                             else
                             {
                                 WIDEN_TRACE("Read {} bytes of header", sz);

                                 proto::Header header;
                                 header.ParseFromString({recvBuf.begin(), recvBuf.begin() + sz});

                                 doReadBody(header.type(), header.body_length());
                             }
                         });
    }

    void Introducer::Session::doReadBody(const std::string &type, uint32_t bodyLen)
    {
        auto self(shared_from_this());
        asio::async_read(socket, asio::buffer(recvBuf, bodyLen),
                         [this, self, type](asio::error_code ec, std::size_t sz)
                         {
                             if (ec)
                             {
                                 WIDEN_ERROR("Error read body: {}", ec.message());
                             }
                             else
                             {
                                 WIDEN_TRACE("Read {} bytes of body", sz);
                                 handleBody(type, std::string(recvBuf.begin(), recvBuf.begin() + sz));
                             }
                             doReadHeaderLen();
                         });
    }

    void Introducer::Session::handleBody(const std::string &type, const std::string &body)
    {
        if (type == "JOIN")
        {
            WIDEN_TRACE("Message is a join request!");
            std::make_shared<JoinRequestHandler>(std::move(socket), body)->start();
        }
        else
        {
            throw std::logic_error(fmt::format("Type <{}> is invalid", type));
        }
    }
}