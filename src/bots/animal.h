#ifndef ANIMAL_H
#define ANIMAL_H
#include <GL/glut.h>
#include <vector>
#include "../../supports/matrix/src/Vectors.h"
//baseclass for the animal

class Animal
{
   protected:
      Vector3 pos;
      int id;
   public:
      Animal();
      Animal(int i);
      ~Animal();
      float getPositionX();
      float getPositionY();
      float getPositionZ();
      int getId();
      void  setPositionX(float new_pos_x);
      void  setPositionY(float new_pos_y);
      void  setPositionZ(float new_pos_z);
      void  setPosition(float new_pos_x, float new_pos_y, float new_pos_z);
      void  drawBox();
      void  thinkMove(float width, float height);
      void  moveRight();
      void  moveLeft();
      void  moveUp();
      void  moveDown();
      virtual void render(){};
      

};

#endif
