/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#include "wxx_socket/online_user.h"
#include "wxx_socket/message_encrypt.hpp"

using namespace wxx_socket;

OnlineUser::OnlineUser()
    : online_time_(0),
      sleep_time_(0),
      online_(false)
{

}

OnlineUser::OnlineUser(char user_ip[], int client_fd)
{
    user_ip_ = user_ip;
    client_fd_ = client_fd;
    online_ = true;
    recive_message_thread_ = boost::thread(boost::bind(&OnlineUser::reciveMessageThread, this));
}

OnlineUser::~OnlineUser()
{
    
}

void OnlineUser::reciveMessageThread()
{
    while (online_)
    {
        message_mutex_.lock();
        memset(recv_message_, 0, MESSAGE_SIZE);
        int recive_result = recv(client_fd_, recv_message_, MESSAGE_SIZE, 0);
        message_mutex_.unlock();
        if (recive_result < 0)
        {
            printf("I'm %s, I recive message failed!\n", user_ip_);
        }
        else if(strlen(recv_message_) != 0)
        {
            printf("I'm %s, I recive message: %s\n", user_ip_, recv_message_);
            sendMessage("I'm server, I recive message success");
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
}

char *OnlineUser::getUserIP()
{
    return user_ip_;
}

bool OnlineUser::sendMessage(char* message)
{
    message = encryptMessage(message);
    int send_result =  send(client_fd_, message, strlen(message), 0);

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