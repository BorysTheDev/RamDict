#include "client.h"

#include <thread>
#include <iostream>

namespace Tests
{
using namespace boost::asio::ip;

Client::Client()
    : _ep(address::from_string("127.0.0.1"), 8081)
    , _sock(ioContext, udp::endpoint(udp::v4(), 0))
{

}

std::thread Client::run()
{
    std::thread echoThreads(
                [this]
    {
        int i = 10;
        char test[] = "test";
        while(--i)
        {
             sleep(1);
            _sock.send_to(boost::asio::buffer(test, 4), _ep);
            auto length = _sock.receive(boost::asio::buffer(_buff, _buff.size()));
            std::cout.write(_buff.data(), length);
            std::cout << std::endl;
            std::cout.flush();
        }
    });
    return echoThreads;

}

} //namespace tests

