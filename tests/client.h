#pragma once

#include <array>
#include <thread>

#include <asio.hpp>


namespace Tests
{
class Client
{
public:
    Client();

    std::thread run();

    void do_send();
    void do_receive();

private:
    asio::io_service _io_context;
    asio::ip::tcp::socket _sock;

    std::array<char, 1024> _buff;
};
}

