/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#include "wxx_socket/tcp_server.h"

using namespace wxx_socket;

TCPServer::TCPServer()
    : server_enable_(true),
      main_thread_(0),
      client_num_(0)
{
    server_sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_ < 0)
    {
        perror("client sock");
        return;
    }
}

TCPServer::~TCPServer()
{
    // server_thread_.join();
    closeServer();
}

bool TCPServer::setServer(bool loopback_address, int port)
{
    int bind_fd, listen_result;
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(port);
    if (loopback_address)
        server_addr_.sin_addr.s_addr = inet_addr(loopback_address_);
    else
        server_addr_.sin_addr.s_addr = htonl(INADDR_ANY);

    bind_fd = bind(server_sock_, (struct sockaddr*)&server_addr_, sizeof(server_addr_));
    if (bind_fd < 0)
    {
        perror("bind");
        return false;
    }
    
    listen_result = listen(server_sock_, 5);
    if (listen < 0)
    {
        perror("listen");
        return false;
    }

    server_enable_ = true;
    
    server_thread_ = boost::thread(boost::bind(&TCPServer::acceptThread, this));
    process_thread_ = boost::thread(boost::bind(&TCPServer::messageProcessThread, this));
    return true;
} 

void TCPServer::acceptThread()
{
    while (server_enable_)
    {
        printf("I'm server\n");
        struct sockaddr_in addr_client;
        socklen_t addr_len = sizeof(addr_client);

        int accept_fd = accept(server_sock_, (struct sockaddr*)&addr_client, &addr_len);
        if (accept_fd < 0)
        {
            printf("accept faile, accept_fd: %d", accept_fd);
            continue;
        }

        printf("create client thread\n");
        char* user_ip = inet_ntoa(addr_client.sin_addr);
        auto user_iterator = online_user_list_.begin();
        for (; user_iterator != online_user_list_.end(); user_iterator++)
        {
            printf("ip: %s , %s\n", (*user_iterator)->getUserIP(), user_ip);
            if (strcmp((*user_iterator)->getUserIP(), user_ip) == 0)
            {
                printf("ip: %s already exists\n", user_ip);
                break;
            }
        }

        if (user_iterator == online_user_list_.end())
        {
             printf("add ip: %s\n", user_ip);
            OnlineUser *new_user = new OnlineUser(user_ip, accept_fd);
            online_user_list_.push_back(new_user);
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

void TCPServer::messageProcessThread()
{

}

// bool TCPServer::sendMessage(char* message)
// {
//     message = encryptMessage(message);
//     int send_result =  send(server_sock_, message, strlen(message), 0);

//     if (send_result < 0)
//     {
//         printf("send error message: %s\n", message);
//         return false;
//     }
//     else
//     {
//         printf("send success message: %s\n", message);
//         return true;
//     }
// }

void TCPServer::addClientNum()
{
    client_num_mutex_.lock();
    client_num_++;
    client_num_mutex_.unlock();
}

void TCPServer::reduceClientNum()
{
    client_num_mutex_.lock();
    client_num_--;
    client_num_mutex_.unlock();
}

bool TCPServer::getServerEnable()
{
    return server_enable_;
}

void TCPServer::closeServer()
{
    close(server_sock_);
}