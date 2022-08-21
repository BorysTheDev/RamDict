#include "client.h"
#include "message.h"

#include <iostream>
#include <thread>

namespace Tests {
using namespace asio::ip;

Client::Client() : _sock(_io_context) {}

std::thread Client::run() {
    tcp::resolver resolver(_io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "8082");
    asio::async_connect(_sock, endpoints, [this](asio::error_code ec, tcp::endpoint) {
        if (!ec) {
            do_send();
        }
    });
    std::thread echoThreads([this] {
        while (true) {
            _io_context.run();
        }
    });
    return echoThreads;
}

void Client::do_send() {
    msg.fill(msg_header::SET, std::span<const char>("test", 4));
    asio::async_write(_sock, asio::buffer(msg.buf),
                      [this](asio::error_code ec, std::size_t /*length*/) {
                          if (!ec) {
                              std::cout << "client send succesfull" << std::endl;
                              do_receive_header();
                          } else {
                              _sock.close();
                          }
                      });
}

void Client::do_receive_header() {
    asio::async_read(
        _sock,
        asio::buffer(&_header, sizeof(_header)),
        [this](asio::error_code ec, std::size_t) {
            if (!ec) {
                std::cout << "msg_type: " << _header.msg_type << ", msg_size: " << _header.msg_size << std::endl;
                _buff.resize(_header.msg_size);
                do_receive_body();
            } else {
                _sock.close();
            }
        });
}

void Client::do_receive_body() {
    asio::async_read(
        _sock,
        asio::buffer(_buff, _buff.size()),
        [this](asio::error_code ec, std::size_t length) {
            if (!ec) {
                std::cout.write(_buff.data(), length) << std::endl;
                do_send();
            } else {
                _sock.close();
            }
        });
}

} // namespace Tests
