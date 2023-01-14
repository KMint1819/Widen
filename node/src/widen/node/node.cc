#include "widen/common/log.hpp"
#include "widen/node/node.hpp"

#include <fstream>

namespace widen
{
    void Node::start()
    {
        std::filesystem::path fileOfHosts("../known_hosts.txt");
        joinFileOfHosts(fileOfHosts);
        mainLoop();
    }

    void Node::joinFileOfHosts(const std::filesystem::path &filePath)
    {
        std::ifstream fin(filePath.string());

        std::string input;
        std::vector<std::string> hostList;
        while (fin >> input)
        {
            hostList.push_back(input);
        }
        joinListOfHosts(hostList);
    }

    void Node::joinListOfHosts(const std::vector<std::string> &hostList)
    {
        WIDEN_TRACE("Joining host lists: {}", hostList);
    }

    void Node::mainLoop()
    {
        ctx.run();
    }
}