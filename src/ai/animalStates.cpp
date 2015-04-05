#include "animalStates.h"
#include "state.h"
#include "../bots/animal.h"
#include <iostream>
#include <stdio.h>
#include "../../supports/matrix/src/Vectors.h"
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
}


void Patrol::Execute(Animal* animal)
{  

  animal->patrol();

  //only tired when patrolling
  animal->increaseFatigue();
  
  if(animal->bored())
  {
    animal->changeDirection();
    animal->setBoredLevel(0.01);
  }

  if (animal->tired())
  {
    animal->changeState(Tired::Instance());
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
}

void Tired::Execute(Animal* animal)
{ 
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



