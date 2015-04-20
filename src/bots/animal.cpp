#include "animal.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <stdio.h>
#include <cassert>
#include "../ai/animalStates.h"

using namespace std;

Animal::Animal():tiredLevel(0),score(0),currentState(Patrol::Instance())
{
 boredLevel = 0;
}

Animal::Animal(int i)
{
 id = i;
}

Animal::~Animal()
{
}

float Animal::getSpeed()
{
  return speed;
}

float Animal::getPositionX()
{
  return pos.x;
}

float Animal::getPositionY()
{
  return pos.y;
}

float Animal::getPositionZ()
{
  return pos.z;
}

int Animal::getId() //classify whether mouse or cats
{
  return id;
}

int Animal::getEntityId() //gives them an ID for each entity.
{
  return entity_id;
}

int Animal::getState()
{
  return state;
}

Vector3 Animal::getPosition()
{
  return pos;
}

int Animal::getMovingDirection()
{
  return dir;
}

int Animal::getScore()
{
  return score;
}

float Animal::getTiredLevel()
{
  return tiredLevel;
}

float Animal::getHungerLevel()
{
  return hunger;
}

void Animal::setEntityId(int e_id)
{
  entity_id = e_id;
}

void Animal::setState(int new_state)
{
  state = new_state;
}

void Animal::setPosition (Vector3 newPosition)
{
   pos.x = newPosition.x;
   pos.y = newPosition.y;
   pos.z = newPosition.z;
}

void Animal::setPositionX(float new_pos_x)
{
  pos.x = new_pos_x;
}

void Animal::setPositionY(float new_pos_y)
{
  pos.y = new_pos_y;
}

void Animal::setPositionZ(float new_pos_z)
{
  pos.z = new_pos_z;
}

void Animal::setPosition(float new_pos_x, float new_pos_y, float new_pos_z)
{
   setPositionX(new_pos_x);
   setPositionY(new_pos_y);
   setPositionZ(new_pos_z);
}

void Animal::setMovingDirection(int new_dir)
{
  dir = new_dir;
}

void Animal::setSpeed(float newSpeed)
{
  speed = newSpeed;
}

void Animal::drawBox()
{
          glBegin(GL_TRIANGLES);
           glVertex3f(-1.0/2,-1.0/2,-1.0/2); // triangle 1 : begin
           glVertex3f(-1.0/2,-1.0/2, 1.0/2);
           glVertex3f(-1.0/2, 1.0/2, 1.0/2); // triangle 1 : end
 
           glVertex3f(1.0/2, 1.0/2,-1.0/2); // triangle 2 : begin
           glVertex3f(-1.0/2,-1.0/2,-1.0/2);
           glVertex3f(-1.0/2, 1.0/2,-1.0/2); // triangle 2 : end
 
           glVertex3f(1.0/2,-1.0/2, 1.0/2); // triangle 3 :begin
           glVertex3f(-1.0/2,-1.0/2,-1.0/2);
           glVertex3f(1.0/2,-1.0/2,-1.0/2);  //triangle 3 :end
 
           glVertex3f(1.0/2, 1.0/2,-1.0/2); // triangle 4 :begin
           glVertex3f(1.0/2,-1.0/2,-1.0/2);
           glVertex3f(-1.0/2,-1.0/2,-1.0/2);// triangle 4 :end
 
           glVertex3f(-1.0/2,-1.0/2,-1.0/2); //triangle 5 :begin
           glVertex3f(-1.0/2, 1.0/2, 1.0/2);
           glVertex3f(-1.0/2, 1.0/2,-1.0/2); // triangle 5 :end
 
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 6 :begin
           glVertex3f(-1.0/2,-1.0/2, 1.0/2);
           glVertex3f(-1.0/2,-1.0/2,-1.0/2); //triangle 6 :end
 
           glVertex3f(-1.0/2, 1.0/2, 1.0/2); //triangle 7 :begin
           glVertex3f(-1.0/2,-1.0/2, 1.0/2);
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 7 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 8 :begin
           glVertex3f(1.0/2,-1.0/2,-1.0/2);
           glVertex3f(1.0/2, 1.0/2,-1.0/2); //triangle 8 :end
 
           glVertex3f(1.0/2,-1.0/2,-1.0/2); //triangle 9 :begin
           glVertex3f(1.0/2, 1.0/2, 1.0/2);
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 9 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 10 :begin
           glVertex3f(1.0/2, 1.0/2,-1.0/2);
           glVertex3f(-1.0/2, 1.0/2,-1.0/2); //triangle 10 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 11 :begin
           glVertex3f(-1.0/2, 1.0/2,-1.0/2);
           glVertex3f(-1.0/2, 1.0/2, 1.0/2); //triangle 11 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2);//triangle 12 :begin
           glVertex3f(-1.0/2, 1.0/2, 1.0/2);
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 12 :end
        glEnd();
}
void Animal::moveRight()
{
  float currentX = getPositionX();
  float s  = getSpeed();
   float newX = currentX + s;
   setPositionX(newX);
}

void Animal::moveLeft()
{
  float currentX = getPositionX();
  float s  = getSpeed();
  float newX = currentX - s;
  setPositionX(newX);  
}


void Animal::moveUp()
{
  float currentY = getPositionY();
  float s  = getSpeed();
  float newY = currentY + s;
  setPositionY(newY);
  
}

void Animal::moveDown()
{
  float currentY = getPositionY();
  float s  = getSpeed();
  float newY = currentY - s;
  setPositionY(newY);
}


void Animal::stop()
{
  Vector3 current = getPosition();
  setPosition(current);
}

void Animal::update()
{
  boredLevel+=0.01;
  if(currentState){
    currentState->Execute(this);
  }
  
}

void Animal::increaseFatigue()
{
  //cout<<"increasing fatigue"<<tiredLevel<<endl;
  tiredLevel += 0.01;
}

void Animal::decreaseFatigue()
{
  //cout<<"decrease fatigue"<<tiredLevel<<endl;
  tiredLevel -= 1.0;
}

void Animal::increaseHunger()
{
 if(hunger<HungerThreshold){
  hunger += 0.01;
  }
}

void Animal::decreaseHunger()
{
 if(hunger>0){
  hunger -= 2.0;
 }
}

void Animal::goToState()
{
   int s = getState();
   //cout<<"in go to state"<<s<<endl;
   switch(s){
       case 0:
         //changes state first before executing
         changeState(Patrol::Instance());
         //cout<<"Now in state Zero"<<endl;
         update(); 
         break;
       case 1:
         //changes state first before executing
         changeState(Tired::Instance());
         //cout<<"Now in state one"<<endl;
         update(); 
         break;
       case 2:
         changeState(Hungry::Instance());
         //cout<<"Now in state two"<<endl;
         update(); 
         break;
       default:
         break;
   }
}


void Animal::changeState(State* new_state)
{
 assert(currentState && new_state);
 currentState -> Exit (this);
 currentState = new_state;
 currentState -> Enter (this);
}

bool Animal::tired()const
{
  if(tiredLevel >= TiredThreshold){return true;}
  return false;
}

bool Animal::bored()const
{
 if(boredLevel>=BoredThreshold){
  return true;
 }
 return false;
}

bool Animal::hungry()const
{
  if(hunger>=HungerThreshold){
    return true;
  }
  return false;

}

void Animal::setBoredLevel(int level)
{
  boredLevel = level;
}


void Animal::setOppositeDirection()
{
  int d = getMovingDirection();
  //cout<<"before channg direction "<<d<<endl; 
  switch (d){
    case 0:
      d = 1; //assign to going bottom
      setMovingDirection(d);
    //  cout<<"after changing direction "<<d<<endl;
      break;
    case 1:
      d = 0; //assign to going up
      setMovingDirection(d);
      //cout<<"after changing direction "<<d<<endl;
      break;
    case 2:
      d =  3; //assign to going left
      setMovingDirection(d);
      //cout<<"after changing direction "<<d<<endl;
      break;
    case 3:
      d = 2; //assign to going right
      setMovingDirection(d);
      //cout<<"after changing direction "<<d<<endl;
      break;
 

  }
}

void Animal::patrol()
{
  move(getMovingDirection());
}

void Animal::changeDirection()
{
   int a = generateRandom(0,3);
   setMovingDirection(a);
}


void Animal::move(int dir)
{
  switch(dir){
   case 0:
     moveUp();
     break;
   case 1:
     moveDown();
     break;
   case 2:
     moveRight();
     break;
   case 3:
     moveLeft();
     break;
   case 4:
     break;
   default:
     stop();
     break;
 }
}

int Animal::generateRandom(int start, int end)
{
    int result = start + (rand() % (int)(end - start + 1));
    return result;
}

