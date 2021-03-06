#include "client.h"
#include <pthread.h>
using namespace std;

Client::Client()
{
    sock = -1;
    port = 0;
    address = "";
}

/**
    Connect to a host on a certain port number
*/
bool Client::conn(string address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }
         
        cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }
     
    //setup address structure
    if(inet_addr(address.c_str()) == (unsigned)-1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
         
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            cout<<"Failed to resolve hostname\n";
             
            return false;
        }
         
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;
 
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
             
            cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;
             
            break;
        }
    }
     
    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
     
    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    struct timeval tv; 
    //3 second timeout
    tv.tv_sec = 3; 
    tv.tv_usec = 0; 
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof tv)) {
        perror("setsockopt"); 
       return -1; 
       } 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    //int flags;
    //flags = fcntl(sock,F_GETFL,0);
    //assert(flags != -1);
    //fcntl(sock, F_SETFL, flags | O_NONBLOCK);


    cout<<"Connected\n";
    return true;
}

/**
    Send data to the connected host
*/
bool Client::send_data(string data)
{

    write(sock , data.c_str() , strlen(data.c_str()+1));
   /* //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }*/
    //cout<<"Data sent\n";
     
    return true;
}

/**
    Receive data from the connected host
*/
string Client::receive(int size)
{
    char buffer[size+1];
    unsigned int ssize = size;
    string reply;
    int n;
    memset(buffer, 0, sizeof(buffer));


    while((n = recv(sock, buffer, sizeof(buffer), 0))>0 || reply.length()==ssize)   
    {
        if(n>0)
            reply.append(buffer, n);
    } 
    
    memset(buffer, 0, sizeof(buffer));
    cout<<reply<<endl;
    return reply;
}

int Client::receiveInt()
{
   int Buf=0;
   int i=0; 
   float milliSec = 1/1000;

   while(recv(sock, &Buf, sizeof(Buf), MSG_NOSIGNAL)<0)
   {
     puts("recv failed");
   }
   i=0;
   i = ntohl(Buf);
   sleep(1*milliSec);
   Buf = 0;
   return i;
}

int Client::receiveMAC()
{

   int Buf;
   int mac = -1;
   int i;
  
   while(mac < 0)
   {
     recv(sock, &Buf, sizeof(Buf), 0);
     i = ntohl(Buf);
     mac = i;
     send_int(0);
   }
   send_int(1);
   i=0;
   Buf = 0;
   //cout<<"mac received in client cpp and is "<<mac<<endl;
   return mac;



}

//make a return int method for AI;

bool Client::sendAiResultStringSize(string d)
{
    //int a = getAnimalSize();
    int a = strlen(d.c_str());
    int net_a =  htonl(a);
    //printf("establishing connections \n"); 
    //sleep(2); 
    //printf("connections success \n");
    
    if( send(sock, (const char*)&net_a, sizeof(a), 0)<0){
     perror("send");
     return false;
    }
    a=0;
    net_a=0;
    
    return true;
    
}

bool Client::send_int(int i)
{
  int net_i = htonl(i);
  if( send(sock, (const char*)&net_i, sizeof(i), 0)<0){
     perror("send");
     return false;
   }
    return true;

}



//assumed no fail
bool Client::keepConnection()
{
    //int a = getAnimalSize();
    int a = 0;
    int net_a =  htonl(a);

    if( send(sock, (const char*)&net_a, sizeof(a), 0)<0){
     perror("send");
     return false;
    }
    return true;
}



void Client::checkIfServerReady()
{

   int a=0;
   bool ready = true;
   while(a!=ready){
     a = receiveInt();
   }
   
}

 
