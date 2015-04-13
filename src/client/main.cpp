#include <pthread.h>
#include <iostream>
#include "client.h"
using namespace std;



//the client should know about the model.
//so that the client could call methods in the model for the ai.
//essentially, 
//model->startServer();
//TheServer->connectClient();
//while true:
//TheServer->tellClientToDoAiCalculations();
//TheServer->Wait();
//Client -> calculateAi();
//Client->sendAiComputationBackToServer();
//Server->recevFromClient();


int main(int argc , char *argv[])
{
    Client c;
    string host;
    int a;

    cout<<"Enter hostname : ";
    cin>>host;
     
    //connect to host
    c.conn(host , 3490);
     
    
    //receive and echo reply
    cout<<"----------------------------\n\n";
    cout<<c.receive(1024);
    cout<<"\n\n----------------------------\n\n";
  
    a = c.receiveInt();
    cout<<a<<endl;
    //c.send_data("hi this is the client");
    //cout<<c.receive(1024)<<endl;
    //c.send_data("second data sent");
    //cout<<c.receive(1024)<<endl;

    while(1){
         
    }
     
    //done
    return 0;
}
