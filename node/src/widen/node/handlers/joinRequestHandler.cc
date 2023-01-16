#include "widen/node/handlers/joinRequestHandler.hpp"
#include "widen/common/log.hpp"

namespace widen
{
    JoinRequestHandler::JoinRequestHandler(tcp::socket socket, const JoinRequest &joinReq)
        : socket(std::move(socket)), joinReq(joinReq)
    {
    }
    void JoinRequestHandler::start()
    {
        WIDEN_TRACE("Received join request from {}/{}:\n{}",
                    socket.remote_endpoint().address().to_string(),
                    socket.remote_endpoint().port(),
                    joinReq.DebugString());
    }
}