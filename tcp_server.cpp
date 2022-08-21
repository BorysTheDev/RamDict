#include "tcp_server.h"

#include <iostream>
#include <thread>

using namespace asio::ip;

TCP_Server::TCP_Server(tcp::endpoint ep)
    : _acceptor(_io_context, std::move(ep)) {}


std::thread TCP_Server::run() {
    std::thread TCP_ServerThread([this] {
        accept();
        _io_context.run();
    });
    return TCP_ServerThread;
}

void TCP_Server::accept() {
    _acceptor.async_accept([this](asio::error_code ec, tcp::socket socket) {
        std::cout << "async_accept" << std::endl;
        if (!ec) {
            Session::make(std::move(socket))->do_receive_header();
        }

        accept();
    });
}
