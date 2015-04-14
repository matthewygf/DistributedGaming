#ifndef CLIENT_H
#define CLIENT_H

//this is modified from tcp_client.cpp.

#include<iostream>    //cout
#include<stdio.h>    //printf
#include<string.h>    //strlen
#include<cstring>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#include <fcntl.h>
#include <cassert>
#include <sys/time.h>
#include "../bots/animal.h"
#include "../ai/state.h"
#include "../ai/animalStates.h"
 
using namespace std;
 
/**
    TCP Client class
*/
class Client
{
private:
    int sock;
    string address;
    int port;
    struct sockaddr_in server;
     
public:
    Client();
    bool conn(string, int);
    bool send_data(string data);
    bool sendAiResult();
    string receive(int);
    int  receiveInt();
    void createStates();
    
    //create Animals
    //ai methods
    //update
    //send to server.


};

#endif
