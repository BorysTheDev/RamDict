#pragma once

#include "message.h"

#include <asio.hpp>

#include <array>
#include <memory>
#include <thread>

#include <iostream> // remove

class Session : public std::enable_shared_from_this<Session> {
public:
    static std::shared_ptr<Session> make(asio::ip::tcp::socket socket) {
        return std::shared_ptr<Session>(new Session(std::move(socket)));
    }

    void do_receive_header() {
        auto callback = [this, self = shared_from_this()](asio::error_code ec,
                                                          std::size_t) {
            if (!ec) {
                std::cout << "msg_type: " << _header.msg_type
                          << ", msg_size: " << _header.msg_size << std::endl;
                _buff.resize(_header.msg_size);
                do_receive_body();
            } else {
                _sock.close();
            }
        };
        asio::async_read(_sock, asio::buffer(&_header, sizeof(_header)),
                         std::move(callback));
    }

    void do_receive_body() {
        auto callback = [this, self = shared_from_this()](asio::error_code ec,
                                                          std::size_t length) {
            if (!ec) {
                std::cout.write(_buff.data(), length) << std::endl;
                do_send();
            } else {
                _sock.close();
            }
        };
        asio::async_read(_sock, asio::buffer(_buff, _buff.size()),
                         std::move(callback));
    }

    void do_send() {
        auto callback = [this, self = shared_from_this()](asio::error_code ec,
                                                          std::size_t length) {
            if (!ec) {
                do_receive_header();
                std::cout << "send server answer" << std::endl;
            } else {
                _sock.close();
            }
        };
        _msg.fill(msg_header::SET, std::span<const char>("tset", 4));
        asio::async_write(_sock, asio::buffer(_msg.buf), std::move(callback));
    }

    ~Session() { std::cout << "session stopped;" << std::endl; }

private:
    Session(asio::ip::tcp::socket socket) : _sock(std::move(socket)) {
        std::cout << "session created;" << std::endl;
    }

    msg_header _header;
    message _msg;
    std::vector<char> _buff;
    asio::ip::tcp::socket _sock;
};
