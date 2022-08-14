#include "tests/client.h"
#include "tcp_server.h"

int main(int , char*[])
{
    TCP_Server server(asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 8082));
    auto sth = server.run();

    Tests::Client client;
    auto cth = client.run();

    sth.join();

    return 0;
}
