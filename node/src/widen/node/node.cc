#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/common/utils.hpp"
#include "widen/common/message_addon.hpp"

#include "widen/node/node.hpp"
#include "widen/node/message_listener.hpp"

#include <fstream>
#include <chrono>

namespace widen
{
    Node::Node(int argc, char **argv)
    {
        std::string introducer;

        if (argc == 1)
        {
            WIDEN_WARN("Running node in a new scope...");
        }
        else if (argc == 2)
        {
            introducer = argv[1];
            WIDEN_WARN("Connecting node to {}...", introducer);

            tcp::resolver resolver(ioc);
            introducerEndpoints = resolver.resolve(argv[1], std::to_string(config::port::message));
        }
    }

    void Node::start()
    {
        if (introducerEndpoints.size() != 0)
        {
            joinViaIntroducer();
        }
        mainLoop();
    }

    std::vector<Identifier> Node::joinViaIntroducer()
    {
        WIDEN_TRACE("Joining via introducer!");
        tcp::socket socket(ioc);
        asio::connect(socket, introducerEndpoints);
        WIDEN_WARN("node connected to {}:{}",
                   socket.remote_endpoint().address().to_v4().to_string(),
                   socket.remote_endpoint().port());

        std::string ip = socket.local_endpoint()
                             .address()
                             .to_v4()
                             .to_string();
        long timestamp = getTimestamp();
        Message message = constructJoinMessage(ip, timestamp);
        WIDEN_TRACE("Join string: {}", message.DebugString());

        std::string sendString = message.SerializeAsString();
        sendString = widen::addLengthToStringFront(sendString);

        std::size_t written = socket.write_some(asio::buffer(sendString));
        WIDEN_TRACE("node wrote {} bytes to join", written);

        //
        std::array<char, 1024> recvBuf;
        int receivedBytes = asio::read(socket, asio::buffer(recvBuf, 4));
        WIDEN_TRACE("Received {} bytes as header", receivedBytes);

        std::string lengthString(recvBuf.begin(), recvBuf.begin() + 4);
        int length = widen::convertLengthString(lengthString);

        receivedBytes = asio::read(socket, asio::buffer(recvBuf, length));
        WIDEN_TRACE("Received {} from introducer", receivedBytes);

        std::string recvString(recvBuf.begin(), recvBuf.begin() + receivedBytes);
        JoinReply joinReply;
        joinReply.ParseFromString(recvString);

        auto rawIdentifiers = joinReply.identifiers();
        return std::vector<Identifier>(rawIdentifiers.begin(), rawIdentifiers.end());
    }

    Message Node::constructJoinMessage(std::string ip, long timestamp)
    {
        Identifier *identifier = new Identifier;
        identifier->set_ip(ip);
        identifier->set_inittimestamp(timestamp);

        JoinRequest *joinReq = new JoinRequest;
        joinReq->set_allocated_identifier(identifier);

        Message message;
        message.set_allocated_joinrequest(joinReq);
        return std::move(message);
    }

    void Node::mainLoop()
    {
        MessageListener listener(ioc, config::port::message);
        listener.start();
        ioc.run();

        WIDEN_WARN("Node exiting...");
    }
}