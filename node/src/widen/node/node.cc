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
    }

    std::vector<Identifier> Node::joinViaIntroducer()
    {
        tcp::socket socket(ioc);
        asio::connect(socket, introducerEndpoints);
        WIDEN_WARN("node connected to {}:{}",
                   socket.remote_endpoint().address().to_v4().to_string(),
                   socket.remote_endpoint().port());

        Identifier identifier;
        std::string ip = socket.local_endpoint()
                             .address()
                             .to_v4()
                             .to_string();
        long timestamp = getTimestamp();
        identifier.set_ip(ip);
        identifier.set_inittimestamp(timestamp);

        JoinRequest joinReq;
        joinReq.set_allocated_identifier(&identifier);

        Message message;
        message.set_allocated_joinrequest(&joinReq);
        WIDEN_TRACE("Join string: {}", message.DebugString());

        std::string protoString = message.SerializeAsString();
        protoString = addDelimToEnd(protoString);

        std::size_t written = socket.write_some(asio::buffer(protoString));
        WIDEN_TRACE("node wrote {} bytes to join", written);

        //

        std::string receivedStr;
        std::size_t receivedSize = asio::read_until(
            socket,
            asio::dynamic_buffer(receivedStr),
            getMessageDelim());
        WIDEN_TRACE("Received {} from introducer", receivedSize);
        receivedStr = removeDelimFromEnd(receivedStr);

        JoinReply joinReply;
        joinReply.ParseFromString(receivedStr);

        auto rawIdentifiers = joinReply.identifiers();
        return std::vector<Identifier>(rawIdentifiers.begin(), rawIdentifiers.end());
    }

    void Node::mainLoop()
    {
        MessageListener listener(ioc, config::port::message);
        listener.start();
        ioc.run();

        // WIDEN_WARN("Node exiting...");
    }
}