#include "animal.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

Animal::Animal()
{

}

Animal::~Animal()
{
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

int Animal::getId()
{
  return id;
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
  //just the width right now
  float currentX = getPositionX();
  //if(currentX < width){
   float newX = currentX + 0.01;
   setPositionX(newX);
  //}
  glTranslatef(getPositionX(),getPositionY(),getPositionZ());
}

void Animal::moveLeft()
{
  float currentX = getPositionX();
  float newX = currentX - 0.01;
  setPositionX(newX);  
  glTranslatef(getPositionX(),getPositionY(),getPositionZ());

}

void Animal::moveUp()
{
  float currentY = getPositionY();
  float newY = currentY + 0.01;
  setPositionY(newY);
  glTranslatef(getPositionX(),getPositionY(),getPositionZ());
}

void Animal::moveDown()
{
  float currentY = getPositionY();
  float newY = currentY - 0.01;
  setPositionY(newY);
  glTranslatef(getPositionX(),getPositionY(),getPositionZ());
}

