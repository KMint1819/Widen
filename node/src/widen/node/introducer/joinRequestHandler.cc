#include "widen/node/introducer/joinRequestHandler.hpp"
#include "widen/common/log.hpp"

#include "widen/common/serialization.hpp"
#include "widen/node/memberlist.hpp"
#include "widen/general.pb.h"

namespace widen
{
    JoinRequestHandler::JoinRequestHandler(tcp::socket socket, const std::string &body)
        : socket(std::move(socket))
    {
        req.ParseFromString(body);
    }

    void JoinRequestHandler::start()
    {
        WIDEN_TRACE("Received join request from {}/{}:\n{}",
                    socket.remote_endpoint().address().to_string(),
                    socket.remote_endpoint().port(),
                    req.DebugString());
        memberlist.emplace_back(
            socket.remote_endpoint().address().to_v4(),
            req.init_timestamp());
        doGossip();
    }

    void JoinRequestHandler::doWrite()
    {
        auto self(shared_from_this());

        Res res;
        for (const auto &member : memberlist)
        {
            proto::Identifier *identifier = res.add_identifiers();
            identifier->set_ip(member.getIp().to_string());
            identifier->set_init_timestamp(member.getInitTime());
        }
        WIDEN_TRACE("Respond body: \nvvvvv\n{}\n^^^^^", res.DebugString());

        std::string resString;
        {
            std::string resBody;
            res.SerializeToString(&resBody);

            uint32_t bodyLen = resBody.length();
            std::string bodyLenString = serializeUInt32(bodyLen);

            resString = bodyLenString + resBody;
        }

        asio::async_write(socket, asio::buffer(resString), [self](asio::error_code ec, std::size_t sz)
                          {
            if(ec)
            {
                WIDEN_ERROR("Error while responding: {}", ec.message());
            }
            else
            {
                WIDEN_TRACE("Responded {} bytes", sz);
            } });
    }
}