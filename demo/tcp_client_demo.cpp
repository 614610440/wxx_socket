#include <iostream>

#include "wxx_socket/tcp_client.h"

using namespace wxx_socket;

int main()
{
    std::cout<<"Hello World"<<std::endl;
    TCPClient client;
    client.conect("127.0.0.1 ", 8888);
    client.sendMessage("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
}