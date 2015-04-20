#include "animalStates.h"
#include "state.h"
#include "../bots/animal.h"
#include <iostream>
#include <stdio.h>
#include "../../supports/matrix/src/Vectors.h"
using namespace std;

//also modified from 'WestWord1' by Mat Buckland 2002 fup@ai-junkie.com

//--------------------------------------methods for Patrol
//In the Server. the animal only execute the state main methods, no need to keep track of the AI.
//Since AI calculation is all in Client.

Patrol* Patrol::Instance()
{
  static Patrol instance;

  return &instance;
}

void Patrol::Enter(Animal* animal)
{
}


void Patrol::Execute(Animal* animal)
{  
  animal->setSpeed(0.01);
  animal->patrol();
  if(animal->bored()) //not a state, so i will leave this here
  {
    animal->changeDirection();
    animal->setBoredLevel(0.01);
  }
  /* this should now only be calculated in Client
  //only tired when patrolling
  //animal->increaseFatigue();
  //animal->increaseHunger();
  
  

  if (animal->tired())
  {
    animal->changeState(Tired::Instance());
  }

  if(animal->hungry())
  {
    animal->changeState(Hungry::Instance());
  }
  */
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
}

void Tired::Execute(Animal* animal)
{ 
  /* calcu
  float t = animal -> getTiredLevel();
  
  if (t<=0 )
  {
     animal->changeState(Patrol::Instance());
  }

  else 
  {*/
  
  if(animal->bored()) //not a state, so i will leave this here
  {
    animal->changeDirection();
    animal->setBoredLevel(0.01);
  }
  
    Vector3 currentPos = animal -> getPosition();
    animal -> setPosition(currentPos);
    animal->decreaseFatigue();
  
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
}

void Hungry::Execute(Animal* animal)
{ 
  animal->setSpeed(0.03);
  animal->patrol();
  /*if(!animal->hungry()){ now should be in the client code.
    animal->changeState(Patrol::Instance());
  }*/
 
 if(animal->bored()) //not a state, so i will leave this here
  {
    animal->changeDirection();
    animal->setBoredLevel(0.01);
  }
}

void Hungry::Exit(Animal* animal)
{
   
}


