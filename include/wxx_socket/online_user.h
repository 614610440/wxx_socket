/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#ifndef _ONLINE_USER_H_
#define _ONLINE_USER_H_

#include <sys/socket.h>
#include <boost/thread.hpp>

#include "wxx_socket/wxx_sock_define.h"

namespace wxx_socket
{

class OnlineUser
{
public:
    OnlineUser();
    OnlineUser(char user_ip[], int client_fd);
    ~OnlineUser();

    void reciveMessageThread();

    char* getUserIP();

    bool sendMessage(char* message);

private:
    char* user_ip_;
    int client_fd_;

    double online_time_;
    double sleep_time_;

    bool online_;

    char recv_message_[MESSAGE_SIZE];
    char send_message_[MESSAGE_SIZE];

    boost::thread recive_message_thread_;
    boost::mutex message_mutex_;
};
}

#endif /* _ONLINE_USER_H_ */