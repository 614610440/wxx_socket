/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#include "wxx_socket/tcp_client.h"
#include "wxx_socket/message_encrypt.hpp"

using namespace wxx_socket;

TCPClient::TCPClient()
{
    client_sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock_ < 0)
    {
        perror("client sock");
        return;
    }
}

TCPClient::~TCPClient()
{
    closeClient();
}

bool TCPClient::conect(char* server_ip, int port)
{
    printf("ip: %s\n", server_ip);
    port_ = port;
    server_ip_ = server_ip;
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(port_);
    server_addr_.sin_addr.s_addr = inet_addr(server_ip_);
    connect_fd_ = connect(client_sock_, (struct sockaddr*)&server_addr_, sizeof(server_addr_));
    if (connect_fd_ < 0)
    {
        perror("connect");
        return false;
    }
    else
    {
        printf("connect success\n");
        return true;
    }
}

bool TCPClient::sendMessage(char* message)
{
    message = encryptMessage(message);
    int send_result =  send(client_sock_, message, strlen(message), 0);

    if (send_result < 0)
    {
        printf("send error message: %s\n", message);
        return false;
    }
    else
    {
        printf("send success message: %s\n", message);
        return true;
    }
    
}

void TCPClient::closeClient()
{
    close(client_sock_);
}