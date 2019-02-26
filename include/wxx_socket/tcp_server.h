/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h> 
#include <boost/thread.hpp>

#include "wxx_socket/wxx_sock_define.h"

namespace wxx_socket
{

class TCPServer
{
public:
    TCPServer();
    ~TCPServer();

    bool setServer(bool loopback_address, int port);
    bool getServerEnable();

    void closeServer();

private:
    const char* loopback_address_ = "127.0.0.1";
    bool server_enable_;
    int server_sock_;
    int port_;
    int client_num_;
    struct sockaddr_in server_addr_;

    boost::thread server_thread_;
    boost::thread_group client_thread_group_;
    boost::mutex client_num_mutex_;

    const pthread_t main_thread_;
    void startServer();
    void clientThread(int client_fd);
    void addClientNum();
    void reduceClientNum();
};
}

#endif /* _TCP_SERVER_H_ */

