#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/common/utils.hpp"

#include "widen/node/node.hpp"
#include "widen/node/distributed_fs/distributed_fs.hpp"
#include "widen/node/failure_detection/failure_detector.hpp"
#include "widen/node/introducer/introducer.hpp"
#include "widen/common/proto_wrapper/join_response.hpp"

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
            memberlist = joinViaIntroducer();
        }
        else
        {
            // Identifier myself;
            WIDEN_TRACE("Self hostname: {}", asio::ip::host_name());
        }
        WIDEN_INFO("Initial memberlist: \n\n{}\n", memberlistDescription(memberlist));

        DistributedFS distributed_fs;
        FailureDetector detector;
        // Introducer introducer;

        distributed_fs.start();
        detector.start();
        // introducer.start();

        ioc.run();
        WIDEN_WARN("Node exiting...");
    }

    Memberlist Node::joinViaIntroducer()
    {
        WIDEN_TRACE("Joining via introducer!");
        tcp::socket socket(ioc);
        asio::connect(socket, introducerEndpoints);
        WIDEN_WARN("node connected to {}:{}",
                   socket.remote_endpoint().address().to_v4().to_string(),
                   socket.remote_endpoint().port());

        JoinRequest req({socket.local_endpoint()
                             .address()
                             .to_v4()
                             .to_string(),
                         getTimestamp()});
        WIDEN_TRACE("Join string: {}", req.toString());
        std::string buffer = req.serialize();

        int nBytes = socket.write_some(asio::buffer(buffer));
        WIDEN_TRACE("node wrote {} bytes to join", nBytes);

        // //
        std::array<char, 1024> recvBuf;
        nBytes = asio::read(socket, asio::buffer(recvBuf, 4));
        WIDEN_TRACE("Received {} bytes as header", nBytes);

        buffer = {recvBuf.begin(), recvBuf.begin() + 4};
        uint32_t length = widen::deserializeNumber<uint32_t>(buffer);

        nBytes = asio::read(socket, asio::buffer(recvBuf, length));
        WIDEN_TRACE("Received {} from introducer", nBytes);

        buffer = {recvBuf.begin(), recvBuf.begin() + nBytes};
        std::string recvString(recvBuf.begin(), recvBuf.begin() + nBytes);

        auto res = JoinResponse::buildDeserialize(recvString);

        auto rawIdentifiers = res.getIdentifiers();
        return {rawIdentifiers.begin(), rawIdentifiers.end()};
    }
}