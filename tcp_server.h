#pragma once

#include <asio.hpp>

#include <array>
#include <thread>
#include <memory>


class Session : public std::enable_shared_from_this<Session> {
public:
    Session(Session&&) = default;

    static std::shared_ptr<Session> make(asio::ip::tcp::socket socket);
    void do_receive();
    void do_send();

    ~Session();
private:
    explicit Session(asio::ip::tcp::socket socket);

    std::array<char, 1024> _buff;
    asio::ip::tcp::socket _sock;
};

class TCP_Server {
public:
    explicit TCP_Server(asio::ip::tcp::endpoint ep);

    std::thread run();

private:
    void accept();

private:
    asio::io_service _io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::array<char, 1024> _buff;
};
