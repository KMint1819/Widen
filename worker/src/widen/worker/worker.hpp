#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <asio.hpp>

namespace widen
{
    using asio::ip::tcp;

    class Worker
    {
    public:
        Worker(int argc, char **argv);
        void start();

    private:
        asio::io_context ioc;
        tcp::resolver::results_type introducerEndpoints;

        void joinViaIntroducer();
        void mainLoop();
    };
}