#ifndef ANIMAL_H
#define ANIMAL_H
#include <GL/glut.h>

//baseclass for the animal

class Animal
{
   protected:
      float pos_x;
      float pos_y;
      float pos_z;
    
   public:
      Animal();
      ~Animal();
      float getPositionX();
      float getPositionY();
      float getPositionZ();
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
