/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#ifndef _WXX_SOCKET_DEFINE_H_
#define _WXX_SOCKET_DEFINE_H_

namespace wxx_socket
{

/*
    message set
*/
#define MESSAGE_SIZE        2048
#define MAX_MESSAGE_SIZE    100 * MESSAGE_SIZE 

/*
    key set
*/
#define MAX_KEY_SIZE        100

/*
    return value set
*/
// message
#define MESSAGE_OUT_SIZE        -2
#define MESSAGE_SEND_ERROR      -1
#define MESSAGE_SEND_SUCCESS    0
#define MESSAGE_DEPART_SUCCESS  1

/*
    message 
*/
struct MessageHead{
    char goal_ip_[16];
    char first_catalog_[16];
    char second_catalog_[16];
    char third_catalog_[16];
};

struct MessageEnd{

};
}

#endif /* _WXX_SOCKET_DEFINE_H_ */