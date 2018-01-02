#pragma once

#include <array>
#include <thread>

#include <boost/asio.hpp>


namespace Tests
{
class Client
{
public:
    Client();

    std::thread run();

private:
    boost::asio::io_service ioContext;
    boost::asio::ip::udp::endpoint _ep;
    boost::asio::ip::udp::socket _sock;

    std::array<char, 1024> _buff;
};
}

