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
    : message_size_(MESSAGE_SIZE)
{
    client_sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock_ < 0)
    {
        perror("client sock");
        return;
    }

    setsockopt(client_sock_, SOL_SOCKET, SO_RCVBUF, (const char*)&message_size_, sizeof(int));
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
        recive_thread_  = boost::thread(boost::bind(&TCPClient::reciveMessageThread, this));
        return true;
    }
}

bool TCPClient::sendMessage(char* message)
{
    message = encryptMessage(message);
    message_mutex_.lock();
    int send_result =  send(client_sock_, message, strlen(message), 0);
    message_mutex_.unlock();
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

void TCPClient::reciveMessageThread()
{   
    while (true)
    {
        message_mutex_.lock();
        memset(recv_message_, 0, MESSAGE_SIZE);
        message_mutex_.unlock();
        int recive_result = recv(client_sock_, recv_message_, MESSAGE_SIZE, 0);
        if (recive_result < 0)
        {
            printf("recive from %s, I recive message failed!\n", server_ip_);
        }
        else if(strlen(recv_message_) != 0)
        {
            printf("recive from %s, I recive message: %s\n", server_ip_, recv_message_);
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

void TCPClient::closeClient()
{
    close(client_sock_);
}