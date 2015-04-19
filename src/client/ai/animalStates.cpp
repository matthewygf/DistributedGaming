#include "animalStates.h"
#include "state.h"
#include "../bots/animal.h"
#include <iostream>
#include <stdio.h>
#include "../../../supports/matrix/src/Vectors.h"
using namespace std;

//also modified from 'WestWord1' by Mat Buckland 2002 fup@ai-junkie.com

//--------------------------------------methods for Patrol

Patrol* Patrol::Instance()
{
  static Patrol instance;

  return &instance;
}

void Patrol::Enter(Animal* animal)
{
  //cout<<"get patrol state ID"<<getStateId()<<endl;
  animal->setState(getStateId());
  //cout<<"animal "<<animal->getEntityId()<<" now executing state "<<animal->getState()<<endl;
}


void Patrol::Execute(Animal* animal)
{  
  //cout<<"animal "<<animal->getEntityId()<<" now executing state "<<animal->getState()<<endl;

  animal->setSpeed(0.01);
  animal->patrol();

  //only tired when patrolling
  animal->increaseFatigue();
  animal->increaseHunger();
  
  if(animal->bored())
  {
    animal->changeDirection();
    animal->setBoredLevel(0.01);
  }

  if (animal->tired()&&animal->hungry())
  {
    animal->changeState(Tired::Instance());
  }

  if(animal->hungry())
  {
    animal->changeState(Hungry::Instance());
  }
  
}


void Patrol::Exit(Animal* animal)
{
}



//----------------------------------------methods for Tired

Tired* Tired::Instance()
{
  static Tired instance;

  return &instance;
}

void Tired::Enter(Animal* animal)
{
 cout<<"get tired state ID"<<getStateId()<<endl;
 animal->setState(getStateId());
}

void Tired::Execute(Animal* animal)
{ 
  //cout<<"animal "<<animal->getEntityId()<<" now executing state "<<animal->getState()<<endl;
  float t = animal -> getTiredLevel();
  
  if (t<=0 )
  {
     animal->changeState(Patrol::Instance());
  }

  else 
  {
    Vector3 currentPos = animal -> getPosition();
    animal -> setPosition(currentPos);
    animal->decreaseFatigue();
  } 
}

void Tired::Exit(Animal* animal)
{ 
}


//----------------------------------------methods for Hungry

Hungry* Hungry::Instance()
{
  static Hungry instance;

  return &instance;
}

void Hungry::Enter(Animal* animal)
{
  cout<<"get Hungry state ID"<<getStateId()<<endl;
  animal->setState(getStateId());
}

void Hungry::Execute(Animal* animal)
{ 
  //cout<<"animal "<<animal->getEntityId()<<" now executing state "<<animal->getState()<<endl;
  animal->setSpeed(0.03);
  animal->patrol();
  if(!animal->hungry()){
    animal->changeState(Patrol::Instance());
  }
 
}

void Hungry::Exit(Animal* animal)
{
   
}


