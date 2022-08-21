#pragma once

#include "message.h"
#include "session.h"

#include <asio.hpp>

#include <array>
#include <thread>
#include <memory>

class TCP_Server {
public:
    explicit TCP_Server(asio::ip::tcp::endpoint ep);

    std::thread run();

private:
    void accept();

private:
    asio::io_service _io_context;
    asio::ip::tcp::acceptor _acceptor;
};
