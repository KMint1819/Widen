#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/common/utils.hpp"
#include "widen/common/serialization.hpp"

#include "widen/node/node.hpp"
#include "widen/node/distributed_fs/distributed_fs.hpp"
#include "widen/node/failure_detection/failure_detector.hpp"
#include "widen/node/introducer/introducer.hpp"
#include "widen/general.pb.h"
#include "widen/introducer.pb.h"

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
            introducerEndpoints = resolver.resolve(argv[1], std::to_string(config::port::introducer));
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
            // add myself to memberlist
            memberlist.emplace_back(getSelfIp(), getTimestamp());
        }
        WIDEN_INFO("Initial memberlist: \n\n{}\n", memberlistDescription(memberlist));

        Introducer introducer(ioc);
        // distributed_fs.start();
        // detector.start();
        introducer.start();

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

        proto::JoinRequest req;
        std::string bodyStr;
        {
            req.set_init_timestamp(getTimestamp());
            req.SerializeToString(&bodyStr);
        }
        WIDEN_TRACE("JoinRequest: {}", req.DebugString());

        proto::Header header;
        std::string headerStr;
        {
            header.set_type("JOIN");
            header.set_body_length(bodyStr.length());
            header.SerializeToString(&headerStr);
        }
        WIDEN_TRACE("JoinHeader: {}", header.DebugString());

        std::size_t sz = 0;
        sz = asio::write(socket, asio::buffer(serializeUInt32(headerStr.length())));
        sz = asio::write(socket, asio::buffer(headerStr));
        sz = asio::write(socket, asio::buffer(bodyStr));

        std::array<char, 8192> buf;
        sz = asio::read(socket, asio::buffer(buf, 4));
        uint32_t bodyLen = deserializeNumber<uint32_t>({buf.begin(), buf.begin() + 4});

        sz = asio::read(socket, asio::buffer(buf, bodyLen));
        assert(bodyLen < 8192);
        assert(bodyLen == sz);

        proto::JoinResponse res;
        res.ParseFromString({buf.begin(), buf.begin() + bodyLen});

        auto identifiers = res.identifiers();
        Memberlist memlist;
        for (const auto &identifier : identifiers)
        {
            memlist.emplace_back(identifier.ip(), identifier.init_timestamp());
        }
        return memlist;
    }
}