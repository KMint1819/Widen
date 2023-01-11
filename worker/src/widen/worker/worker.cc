#include "widen/common/log.hpp"
#include "widen/common/config.hpp"
#include "widen/worker/worker.hpp"
#include "widen/worker/message_listener.hpp"

#include <fstream>

namespace widen
{
    void Worker::start()
    {
        std::filesystem::path fileOfHosts("../known_hosts.txt");
        joinFileOfHosts(fileOfHosts);
        mainLoop();
    }

    void Worker::joinFileOfHosts(const std::filesystem::path &filePath)
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

    void Worker::joinListOfHosts(const std::vector<std::string> &hostList)
    {
        WIDEN_TRACE("Joining host lists: {}", hostList);
    }

    void Worker::mainLoop()
    {
        std::make_shared<MessageListener>(ioc, config::port::message)->start();
        ioc.run();
    }
}