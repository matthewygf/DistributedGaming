#include <pthread.h>
#include <iostream>
#include "client.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
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
    vector<Cat> cats;
    
    cout<<"Enter hostname : ";
    cin>>host;
     
    //connect to host
    c.conn(host , 3490);
     
    
    //receive and echo reply
    cout<<"----------------------------\n\n";
    cout<<c.receive(1024);
    cout<<"\n\n----------------------------\n\n";
  
    ////////////////////////////////////////////////////////////
    //here to receive all the require information before calculating Ai.
    a = c.receiveInt();
    cout<<a<<endl;
   
    for(int i = 0; i<a; i++){
      Cat c;
      cats.push_back(c);
    }
    int i = cats.size();
    cout<<"client have cats size "<<i<<endl;
    cout<<c.receive(1024)<<endl;
    ///////////////////////////////////////////////////////////////

    //keep send results to server.
    while(1){
         c.sendAiResult();
         sleep(2);
    }
     
    //done
    return 0;
}
