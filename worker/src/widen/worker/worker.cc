#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/common/utils.hpp"
#include "widen/common/message_addon.hpp"

#include "widen/worker/worker.hpp"
#include "widen/worker/message_listener.hpp"

#include <fstream>
#include <chrono>

namespace widen
{
    Worker::Worker(int argc, char **argv)
    {
        std::string introducer;

        if (argc == 1)
        {
            WIDEN_WARN("Running worker in a new scope...");
        }
        else if (argc == 2)
        {
            introducer = argv[1];
            WIDEN_WARN("Connecting worker to {}...", introducer);

            tcp::resolver resolver(ioc);
            introducerEndpoints = resolver.resolve(argv[1], std::to_string(config::port::message));
        }
    }

    void Worker::start()
    {
        if (introducerEndpoints.size() > 0)
        {
            std::vector<Identifier> identifiers = joinViaIntroducer();
            for (const auto &identifier : identifiers)
            {
                WIDEN_TRACE("Identifier: {}", identifier.DebugString());
            }
        }
        // mainLoop();
    }

    std::vector<Identifier> Worker::joinViaIntroducer()
    {
        tcp::socket socket(ioc);
        asio::connect(socket, introducerEndpoints);
        WIDEN_WARN("Worker connected to {}:{}",
                   socket.remote_endpoint().address().to_v4().to_string(),
                   socket.remote_endpoint().port());

        Message message;
        {
            JoinRequest joinReq;
            {
                std::string ip = socket.local_endpoint()
                                     .address()
                                     .to_v4()
                                     .to_string();
                long timestamp = getTimestamp();
                Identifier identifier;
                {
                    identifier.set_ip(ip);
                    identifier.set_inittimestamp(timestamp);
                }
                joinReq.set_allocated_identifier(&identifier);
            }
            message.set_allocated_joinrequest(&joinReq);
            WIDEN_TRACE("Join string: {}", message.DebugString());
        }

        std::string protoString = message.SerializeAsString();
        protoString = addDelimToEnd(protoString);

        std::size_t written = socket.write_some(asio::buffer(protoString));
        WIDEN_TRACE("Worker wrote {} bytes to join", written);

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

    void Worker::mainLoop()
    {
        std::make_shared<MessageListener>(ioc, config::port::message)->start();
        ioc.run();
    }
}