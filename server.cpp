#include "server.h"

#include <iostream>
#include <thread>

using namespace boost::asio::ip;
Server::Server() : _sock(_ioContext, udp::endpoint(udp::v4(), 8081))
{
}

void Server::receive()
{
    _sock.async_receive_from(
        boost::asio::buffer(_buff, _buff.size()),
        _clientEP,
        [this](boost::system::error_code ec, std::size_t bytes)
        {
            if (!ec && bytes > 0)
            {
                std::cout.write(_buff.data(), bytes);
                std::cout << std::endl;
                send();
            }
            else
            {
                receive();
            }
        });
}

void Server::send()
{
    auto response = "ok";
    _sock.async_send_to(
        boost::asio::buffer(response, std::strlen(response)),
        _clientEP,
        [this](boost::system::error_code /*ec*/, size_t /*bytes*/)
        {
            receive();
        });
}

std::thread Server::run()
{
    std::thread serverThread([this]
    {
        receive();
        while(true)
        {
            _ioContext.run();
        }
    });
    return serverThread;
}
