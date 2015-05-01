#include <pthread.h>
#include <iostream>
#include "client.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
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



void createCats(vector<Cat>&cats,vector<int> c_id,int tWidth)
{
    for(unsigned int i = 0;i<c_id.size();i++){
      Cat c;
      c.setEntityId(c_id[i]);
      c.setMapSize(tWidth);
      c.setHungerLevel(0);
      cats.push_back(c);
    } 
    cout<<"CATS VECTOR NOW HAVE "<<cats.size()<<endl;
    
}

void createMice(vector<Mouse>&mice,vector<int> id,int tWidth)
{
    for(unsigned int i = 0;i<id.size();i++){
      Mouse m;
      m.setEntityId(id[i]);
      m.setMapSize(tWidth);

      m.setHungerLevel(0);
      mice.push_back(m);
    } 
    cout<<"MICE VECTOR NOW HAVE "<<mice.size()<<endl;
}

void aiUpdate(vector<Cat>&c, vector<Mouse>&m,string &result)
{
  for(unsigned int i=0;i<c.size();i++)
      {
          c[i].update();
          int cid = c[i].getEntityId();
          int sid = c[i].getState();
          //append cat first
          stringstream s1;
          s1 << cid;
          string str1 = s1.str();
          result.append(str1);
          result.append(":");
          stringstream s2;
          s2 << sid;
          string str2 = s2.str();
          result.append(str2);
          result.append(",");
          //cout<<"updated status in cat "<<cid<<" and in state "<<sid<<endl;   
       }
       
      if(m.size()>0)
      { 
          result.append("m");
       for(unsigned int i=0;i<m.size();i++)
       {   
           m[i].update();
           int mid = m[i].getEntityId();
           int sid = m[i].getState();
           stringstream s1;
           s1 << mid;
           string str1 = s1.str();
           result.append(str1);
           result.append(":");
           stringstream s2;
           s2 << sid;
           string str2 = s2.str();
           result.append(str2);
           result.append(",");
           //cout<<"updated status in mouse "<<mid<<" and in state "<<sid<<endl;
        }
      }
}


void calculateAi(vector<Cat>&c, vector<Mouse>&m, vector<string>&tokens,string &backToClient)
{
   for(int i=0;i<tokens.size();i++)
   {
     string t = tokens[i];
     string delimiter = ":";
     size_t pos = 0;
     string etoken;
     
     while ((pos = t.find(delimiter)) != string::npos) 
      {
        etoken = t.substr(0, pos);
        t.erase(0, pos + delimiter.length());
      }
      if(etoken=="m_eaten") //mice that got eaten
      {
        int s     = atoi(t.c_str());
        if(m.size()>0)
        {
         for(unsigned int i=0;i<m.size();i++)
         {
           if(s == m[i].getEntityId())
           {
            cout<<"m "<<m[i].getEntityId()<<" going to be deleted"<<endl;
            m.erase(m.begin() + i);
           }
         }
        } 
      }
      else if (etoken=="c_eat")
      {
        int s     = atoi(t.c_str());
        for(unsigned int i=0;i<c.size();i++)
        {
          if(s == c[i].getEntityId())
          {
            c[i].caught();
          }
          
        }
      }
      else
      {
        int s     = atoi(t.c_str());
        if(m.size()>0)
        {
         for(unsigned int i = 0; i<m.size();i++)
         {
           if(s==m[i].getEntityId())
           {
             m[i].ateCheese();
           }
         }
        }
      } 
   }

   aiUpdate(c,m,backToClient);
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

int generateRandom(int start, int end)
{
    int result = start + (rand() % (int)(end - start + 1));
    return result;
    
}

int main(int argc , char *argv[])
{
    Client c;
    string host;
    int a,b,temp,mac,temp_mac,tWidth,entitiesLength;
    int catAteMiceSize;
    int old_catAteMiceSize = 0;
    int datasize = 0;
    string entities;
    string update="";
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
    float milliSec = 1/1000;
    bool connected = false;

    vector<int> catsId;
    vector<int> miceId;
    vector<int> m_eatenId;//mouse that got eaten at that frame

    vector<Cat> cats;
    vector<Mouse> mice;

    cout<<"Enter hostname : ";
    //cin>>host; 
    //connect to host
    c.conn("129.11.146.62" , 3490);
    
    c.checkIfServerReady();
    cout<<"server is ready"<<endl;
    connected = true;
    //receive and echo connection reply.
    cout<<"----------------------------\n\n";
    cout<<c.receive(1024);
    cout<<"\n\n----------------------------\n\n";
    int id;
    cin>>id;
    while(!c.send_int(id))
    {
    }
    cout<<id<<" send"<<endl;
    
    tWidth = c.receiveInt();
    cout<<"tWidth = "<<tWidth<<endl;
    
    entitiesLength = c.receiveInt();
    cout<<"entities length is "<<entitiesLength<<endl;
    
    
    entities = c.receive(entitiesLength+1);
    cout<<entities<<endl;
    
    e_cats = entities.substr(0, entities.find(splitM));
    e_mice = entities.substr(entities.find(splitM)+1, entities.length());
    getEntitiesIdFromServer(catsId,e_cats);
    getEntitiesIdFromServer(miceId,e_mice);
    
    //give the cats the cats ID.
    createCats(cats,catsId,tWidth);
    //give the mice the mice ID.
    createMice(mice,miceId,tWidth);
    
    while(connected)
    {
      c.keepConnection();
      string stateResults = "";
      datasize = c.receiveInt();
      cout<<datasize<<endl;
      
      if(datasize!=0)
      {
        vector<string> tokens;
        update=c.receive(datasize);
        
        istringstream ss(update);
        string token;
        while(getline(ss, token, ','))
         {
            //store in a string vector for calculation
            tokens.push_back(token);
         }
        calculateAi(cats,mice,tokens,stateResults); 
        c.sendAiResultStringSize(stateResults); 
      }
      else
      {
        aiUpdate(cats,mice,stateResults);
        c.sendAiResultStringSize(stateResults); 
      }
      
      sleep(1*milliSec);
      c.send_data(stateResults);
      sleep(1*milliSec);
      datasize=0;
      
    }
    
    /*
std::string input = "abc,def,ghi";
std::istringstream ss(input);
std::string token;

while(std::getline(ss, token, ',')) {
    std::cout << token << '\n';
}

           
            cout<<etoken<<endl;
            cout<<token<<endl;
            
            
            

    //should be in a while loop keep updating how many animals are left.
    while(1){
    string stateResults = "";
    vector<int> catAteMouseId;//cat that ate a mouse for AI hungry state
    vector<int> mice_ate_cheese;//startover everyframe
    //just to keep connection going. and first make this to set the cats n mice to starts walkin.
    
    sleep(1);
    //keep updating mice size. or update which one has got eaten.
    b = c.receiveInt();
    cout<<"mice size is "<<b<<" successfully received in client"<<endl;
    sleep(1);
    a = c.receiveInt(); // number of mice has been eaten, and the number of cat has eaten
    cout<<"Numof Mice has been eaten "<<a<<" successfully received in client"<<endl;
    
    //only run when some mouse has been eaten
    if(a>0 && (abs(temp-a))>0){
      sleep(1);
      data = c.receive(512);
      miceEaten = data.substr(0, data.find(splitC));
      cout<<"mice that has eaten"<<miceEaten<<endl;
      catAte = data.substr(data.find(splitC)+1, data.find(splitH)-2);
      cout<<"cat that has eaten "<<catAte<<endl;
      getEntitiesIdFromServer(m_eatenId,miceEaten);
      getEntitiesIdFromServer(catAteMouseId,catAte);
      catAteMiceSize = catAteMouseId.size();
      deleteMiceFromVector(mice,m_eatenId);
      cout<<"num of mice that has been eaten "<<m_eatenId.size()<<endl;
      cout<<"cat's entity ID has been added to the vector catAteMouse "<<catAteMiceSize-     
      old_catAteMiceSize<<endl;
    }
    
    sleep(1);
    mac=c.receiveInt();
    cout<<"mice that ate cheese has been received and it is : "<<mac<<endl;
    if(mac!=0 && (abs(temp_mac - mac))!=0)//if mice ate cheese size has been changed
    {
    //then receive who ate some cheese
     miceAteCheese = c.receive(512);
     //store to the vector
     getEntitiesIdFromServer(mice_ate_cheese,miceAteCheese);
     cout<<"received "<<mice_ate_cheese.size()<< " mice that ate cheese"<<endl;
    }
    
    //calculate Ai
    calculateAi(cats,mice,catAteMouseId,mice_ate_cheese,stateResults);
    
    //send back to server.
    //send the number of bytes first
    c.sendAiResultStringSize(stateResults);
    sleep(1);
    if(stateResults.length()>0){
     c.send_data(stateResults);
    }
    
    old_catAteMiceSize = catAteMiceSize;
    temp = a;
    temp_mac = mac;
    b=0;
    a=0;
    sleep(2);
   }*/

    //done
    return 0;
}
