#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/common/utils.hpp"
#include "widen/worker/worker.hpp"
#include "widen/worker/message_listener.hpp"
#include "widen/messages.pb.h"

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
            introducerEndpoints = resolver.resolve(argv[1], argv[2]);
        }
    }

    void Worker::start()
    {
        if (introducerEndpoints.size() > 0)
            joinViaIntroducer();
        mainLoop();
    }

    void Worker::joinViaIntroducer()
    {
        tcp::socket socket(ioc);
        asio::connect(socket, introducerEndpoints);
        WIDEN_WARN("Worker connected to {}:{}",
                   socket.remote_endpoint().address().to_v4(),
                   socket.remote_endpoint().port());

        std::string ip = socket.local_endpoint()
                             .address()
                             .to_v4()
                             .to_string();
        long timestamp = getTimestamp();
        Identifier identifier;
        identifer

            identifier.set_ip();
        socket.local_endpoint().address().to_v4().to_string();
        joinReq.identifier
            Message message;
    }

    void Worker::mainLoop()
    {
        std::make_shared<MessageListener>(ioc, config::port::message)->start();
        ioc.run();
    }
}