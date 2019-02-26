/*******************************************************************************
* Copyright 2019 wxx
*
* You can contact me by email:
*   614610440@qq.com
*
*******************************************************************************/

#ifndef _MESSAGE_ENCRYPT_HPP_
#define _MESSAGE_ENCRYPT_HPP_
#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
namespace wxx_socket
{

 /* define */
char* encryptMessage(char* message);
char* decryptMessage(char* message);
void  initKey(int public_key[], int private_key[]);

int ProducePrimeNumber(int prime[]);

/* realize */
char* encryptMessage(char* message)
{
    return "test";
}

char* decryptMessage(char* message)
{

}

// void initKey(int public_key[], int private_key[])
// {
    
// }

void initKey(int rsa_n, int rsa_e, int rsa_d)
{
     //取出1000内素数保存在prime[]数组中
     int prime[5000];
     int count_prime = ProducePrimeNumber(prime);
}

int ProducePrimeNumber(int prime[])
{

}

}

#endif /* _MESSAGE_ENCRYPT_HPP_ */