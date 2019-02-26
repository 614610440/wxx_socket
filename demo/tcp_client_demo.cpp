#include <iostream>
#include <stdio.h>
#include <string.h>

#include "wxx_socket/tcp_client.h"

using namespace wxx_socket;

int main()
{
    std::cout<<"Hello World"<<std::endl;
    TCPClient client;
    client.conect("127.0.0.1 ", 8888);

    int i = 0;
    while (1)
    {
        i++;
        char* message;
        printf("send...\n");
        // scanf("%s", &message);
        client.sendMessage("message");
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
    
}