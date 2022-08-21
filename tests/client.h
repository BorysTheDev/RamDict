#pragma once

#include "message.h"

#include <asio.hpp>

#include <array>
#include <thread>

namespace Tests
{
class Client
{
public:
    Client();

    std::thread run();

    void do_send();
    void do_receive_header();
    void do_receive_body();

private:
    asio::io_service _io_context;
    asio::ip::tcp::socket _sock;

    msg_header _header;
    message msg;
    std::vector<char> _buff;
};
}

