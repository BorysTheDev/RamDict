#include "tests/client.h"
#include "server.h"

int main(int argc, char *argv[])
{
    Server server;
    auto sth = server.run();

    Tests::Client client;
    auto cth = client.run();

    sth.join();

    return 0;
}
