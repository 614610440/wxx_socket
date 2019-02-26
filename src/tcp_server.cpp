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
    
    server_thread_ = boost::thread(boost::bind(&TCPServer::startServer, this));
    return true;
} 

void TCPServer::startServer()
{
    while (server_enable_)
    {
        printf("I'm server\n");
        struct sockaddr_in addr_client;
        socklen_t addr_len;

        int accept_fd = accept(server_sock_, (struct sockaddr*)&addr_client, &addr_len);
        if (accept_fd < 0)
        {
            printf("accept faile, accept_fd: %d", accept_fd);
            continue;
        }

        printf("create client thread\n");
        boost::thread *client_thread = new boost::thread(boost::bind(&TCPServer::clientThread, this, accept_fd));
        client_thread_group_.add_thread(client_thread);
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

void TCPServer::clientThread(int client_fd)
{
    addClientNum();
    while (server_enable_)
    {
        printf("I'm client: %d\n", client_fd);
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

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