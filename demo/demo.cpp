#include <iostream>

#include "wxx_socket/tcp_client.h"

using namespace wxx_socket;

int main()
{
    std::cout<<"Hello World"<<std::endl;
    TCPClient client;
    client.test();
}