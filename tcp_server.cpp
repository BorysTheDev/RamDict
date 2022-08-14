#include "tcp_server.h"

#include <iostream>
#include <thread>

using namespace asio::ip;

std::shared_ptr<Session> Session::make(tcp::socket socket) {
    return std::shared_ptr<Session>(new Session(std::move(socket)));
}

Session::Session(tcp::socket socket) : _sock(std::move(socket)) {
    std::cout << "session created;" << std::endl;
}

void Session::do_receive() {
    asio::async_read(
        _sock,
        asio::buffer(_buff, _buff.size()),
        [this, self = shared_from_this()](asio::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout.write(_buff.data(), length) << std::endl;
                do_send();

            } else {
                _sock.close();
            }
        });
}

void Session::do_send() {
    auto test = "tset";
    asio::async_write(
        _sock,
        asio::buffer(test, 4),
        [this, self = shared_from_this()](asio::error_code ec, std::size_t length) {
            if (!ec) {
                do_receive();
                std::cout << "send server answer" << std::endl;
            } else {
                _sock.close();
            }
        });
}

Session::~Session() { std::cout << "session stopped;" << std::endl; }

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
            Session::make(std::move(socket))->do_receive();
        }

        accept();
    });
}
