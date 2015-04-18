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
#include "bots/animal.h"
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

void calculateAi(vector<Cat>&c, vector<Mouse>&m)
{
  for(unsigned int i=0;i<c.size();i++)
  {
    c[i].update();
    //cout<<c[i].getEntityId()<<" updating"<<endl;
    //cout<<c[i].getHungerLevel()<<endl;
  }
}

void deleteMiceFromVector(vector<Mouse>&m, vector<int>&id)
{
 if(m.size()!=0){
  for(unsigned int i = 0 ; i<m.size();i++)
  {
    for(unsigned int j = 0; j<id.size();j++)
     {
      if(m[i].getEntityId()==id[j])
       {
         cout<<"m "<<m[i].getEntityId()<<" going to be deleted"<<endl;
         m.erase(m.begin() + i);

       }
     }
   }
 }
 cout<<"mice size is now "<<m.size()<<endl;
}

int main(int argc , char *argv[])
{
    Client c;
    string host;
    int a,b,temp;
    string entities;
    string splitM = "m";
    string splitC = "c";
    string splitH = "h";
    string e_cats;
    string e_mice;
    //string e_mice_ate_cheese;
    string data;
    string miceEaten;
    string catAte;
    string miceAteCheese;
    vector<int> catsId;
    vector<int> miceId;
    vector<int> m_eatenId;//mouse that got eaten at that frame
    vector<int> mice_ate_cheese;
    vector<Cat> cats;
    vector<Mouse> mice;

    cout<<"Enter hostname : ";
     
    //connect to host
    c.conn("localhost" , 3490);
    
    //receive and echo connection reply.
    cout<<"----------------------------\n\n";
    cout<<c.receive(1024);
    cout<<"\n\n----------------------------\n\n";
   
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
    vector<int> catAteMouseId;//cat that ate a mouse for AI hungry state
    //send default Ai result when connected for let cats n mice starts walkin.;
    c.sendAiResult();
    sleep(1);
    //keep updating mice size. or update which one has got eaten.
    b = c.receiveInt();
    cout<<"mice size is "<<b<<" successfully received in client"<<endl;
    a = c.receiveInt();
    cout<<"Numof Mice has been eaten "<<a<<" successfully received in client"<<endl;
    //catEatenMiceSize=c.receiveInt();
    //cout<<"Num cat has eaten mice "<<catEatenMiceSize<<endl;

    //receive the mice that has been eaten and cat that has eaten.
    if(a!=0 && (abs(temp-a))!=0){
      data = c.receive(512);
      sleep(1);
      miceEaten = data.substr(0, data.find(splitC));
      catAte = data.substr(data.find(splitC)+1, data.find(splitH)-2);
      //miceAteCheese = data.substr(data.find(splitH)+1,data.length());
      cout<<"cat that has eaten "<<catAte<<endl;
      getEntitiesIdFromServer(m_eatenId,miceEaten);
      getEntitiesIdFromServer(catAteMouseId,catAte);
     // getEntitiesIdFromServer(mice_ate_cheese,miceAteCheese);
      deleteMiceFromVector(mice,m_eatenId);
      cout<<"num of mice that has been eaten "<<m_eatenId.size()<<endl;
      cout<<"cat's entity ID has been added to the vector "<<catAteMouseId.size()<<endl;
    }

    cout<<c.receiveInt()<<endl;
   
    //calculate Ai
    //calculateAi(cats,mice,catAteMouseId);
    //append the string ai result(cats);
    //append the string ai result(mice);
    temp =a;
    b=0;
    a=0;

    }
    
    sleep(1);
    //done
    return 0;
}
