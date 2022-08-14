#include "client.h"

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
    char test[] = "test";
    asio::async_write(_sock, asio::buffer(test, 4),
                      [this](asio::error_code ec, std::size_t /*length*/) {
                          if (!ec) {
                              std::cout << "send succesfull" << std::endl;
                              do_receive();
                          } else {
                              _sock.close();
                          }
                      });
}

void Client::do_receive() {
    asio::async_read(_sock, asio::buffer(_buff, _buff.size()),
                     [this](asio::error_code ec, std::size_t length) {
                         if (!ec) {
                             do_send();
                             std::cout.write(_buff.data(), length);
                         } else {
                             _sock.close();
                         }
                     });
}

} // namespace Tests
