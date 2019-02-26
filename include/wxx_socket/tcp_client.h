/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <boost/thread.hpp>

#include "wxx_socket/wxx_sock_define.h"

namespace wxx_socket
{

class TCPClient
{
public:
    TCPClient();
    ~TCPClient();

    bool conect(char* server_ip, int port);
    bool sendMessage(char* message);
    bool sendEncryptMessage(char* message);
    
    void reciveMessageThread();
    void closeClient();

private:
    int client_sock_;
    int port_;
    int connect_fd_;
    char* server_ip_;
    struct sockaddr_in server_addr_;

    boost::thread recive_thread_;
    boost::mutex message_mutex_;

    char recv_message_[MESSAGE_SIZE];
    char send_message_[MESSAGE_SIZE];
    char private_key_[MAX_KEY_SIZE];
    char public_key_[MAX_KEY_SIZE];

    int rsa_e_;
    int rsa_d_;
    int rsa_n_;
};
}

#endif /* _TCP_CLIENT_H_ */

