#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <asio.hpp>

namespace widen
{
    class Worker
    {
    public:
        void start();

    private:
        asio::io_context ioc;

        void joinFileOfHosts(const std::filesystem::path &filePath);
        void joinListOfHosts(const std::vector<std::string> &hostList);
        void mainLoop();
    };
}