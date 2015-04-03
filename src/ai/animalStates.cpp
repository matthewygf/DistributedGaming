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
  //cout<<"starting to patrol, looking for other animals"<<endl;
}


void Patrol::Execute(Animal* animal)
{  

  animal->move(animal->getMovingDirection());

  //only tired when patrolling
  animal->increaseFatigue();

  //cout << "patrolling" << endl;

  //if enough gold mined, go and put it in the bank
  //if (animal->Full())
  //{
    //pMiner->ChangeState(VisitBankAndDepositGold::Instance());
  //}

  if (animal->tired())
  {
    animal->move(4);
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
  cout<<"tired"<<endl;
}

void Tired::Execute(Animal* animal)
{ 
  float t = animal -> getTiredLevel();
  //if miner is not fatigued start to dig for nuggets again.
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



