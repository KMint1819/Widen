#include "widen/node/introducer/joinRequestHandler.hpp"
#include "widen/common/log.hpp"

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
    }
}