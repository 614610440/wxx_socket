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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h> 
#include <boost/thread.hpp>

#include "wxx_socket/wxx_sock_define.h"
#include "wxx_socket/online_user.h"

namespace wxx_socket
{

class TCPServer
{
public:
    TCPServer();
    ~TCPServer();

    bool setServer(bool loopback_address, int port);
    bool getServerEnable();
    // bool sendMessage(char* message);

    void closeServer();

private:
    const char* loopback_address_ = "127.0.0.1";
    bool server_enable_;
    int server_sock_;
    int port_;
    int client_num_;
    struct sockaddr_in server_addr_;

    boost::thread server_thread_;
    boost::thread process_thread_;
    boost::mutex client_num_mutex_;

    std::list<OnlineUser*> online_user_list_;

    const pthread_t main_thread_;
    void acceptThread();
    void messageProcessThread();
    void addClientNum();
    void reduceClientNum();
};
}

#endif /* _TCP_SERVER_H_ */

