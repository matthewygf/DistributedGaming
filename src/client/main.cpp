#include <pthread.h>
#include <iostream>
#include "client.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <random>
#include <cmath>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
#include <vector>
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

bool checkMiceEaten(vector<int>&eaten, int i)
{
  if(eaten.size() != 0){
    //for ()
    cout<<"at least bigger than zero"<<endl;
    return true;
   }else{cout<<"Not"<<endl;
    return false;}
} 

void getEntitiesIdFromServer(vector<int>&e, string entities)
{
  stringstream ss(entities);
  int i;

    while (ss >> i)
      {
        
         e.push_back(i);
 

      if (ss.peek() == ','){
        ss.ignore();
      }
 }
}



void createCats(vector<Cat>&cats,vector<int> c_id)
{
    for(unsigned int i = 0;i<c_id.size();i++){
      Cat c;
      c.setEntityId(c_id[i]);
      cats.push_back(c);
    } 
    cout<<"CATS VECTOR NOW HAVE "<<cats.size()<<endl;
}

void createMice(vector<Mouse>&mice,vector<int> id)
{
    for(unsigned int i = 0;i<id.size();i++){
      Mouse m;
      m.setEntityId(id[i]);
      mice.push_back(m);
    } 
    cout<<"MICE VECTOR NOW HAVE "<<mice.size()<<endl;
}


int main(int argc , char *argv[])
{
    Client c;
    string host;
    int a,b,temp;
    string entities;
    string splitM = "m";
    
    string e_cats;
    string e_mice;
    string eaten;
    vector<int> catsId;
    vector<int> miceId;
    vector<int> m_eatenId;
    vector<int> m_new_eatenId;
    vector<Cat> cats;
    vector<Mouse> mice;
    cout<<"Enter hostname : ";
    cin>>host;
     
    //connect to host
    c.conn(host , 3490);
    
    //receive and echo connection reply.
    cout<<"----------------------------\n\n";
    cout<<c.receive(1024);
    cout<<"\n\n----------------------------\n\n";
    if(m_eatenId.size()!=0){
    cout<<"m_eatenID size before"<<m_eatenId.size()<<endl;}
    sleep(2);
    
    ////////////////////////////////////////////////////////////
    //here to receive all the require information before calculating Ai.
    entities = c.receive(512);
    //sleep(1);
    e_cats = entities.substr(0, entities.find(splitM));
    e_mice = entities.substr(entities.find(splitM)+1, entities.length());
    
    getEntitiesIdFromServer(catsId,e_cats);
    getEntitiesIdFromServer(miceId,e_mice);
    
    //give the cats the cats ID.
    createCats(cats,catsId);
    //give the mice the mice ID.
    createMice(mice,miceId);
    ///////////////////////////////////////////////////////////////
    
    sleep(1);
    //should be in a while loop keep updating how many animals are left.
    while(1){
    //send default Ai result when connected for let cats n mice starts walkin.;
    c.sendAiResult();
    sleep(1);
    //keep updating mice size. or update which one has got eaten.
    b = c.receiveInt();
    cout<<"mice size is "<<b<<" successfully received in client"<<endl;

    a = c.receiveInt();
    cout<<"miceEaten size is "<<a<<" successfully received in client"<<endl;
    if(a!=0&& (abs(temp-a))!=0){
    eaten = c.receive(512);
    cout<<eaten<<endl;
    getEntitiesIdFromServer(m_eatenId,eaten);
    cout<<m_eatenId.size()<<endl;
    }
    temp =a;
    
    }
    
  
     

    //keep send results to server.
    //while(1){
      //   c.sendAiResult();
       //  sleep(2);
    //}
     
    //done
    return 0;
}
