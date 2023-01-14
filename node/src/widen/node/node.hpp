#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <asio.hpp>

namespace widen
{
    class Node
    {
    public:
        void start();

    private:
        asio::io_context ctx;

        void joinFileOfHosts(const std::filesystem::path &filePath);
        void joinListOfHosts(const std::vector<std::string> &hostList);
        void mainLoop();
    };
}