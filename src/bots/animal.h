#ifndef ANIMAL_H
#define ANIMAL_H
#include <GL/glut.h>
#include <vector>
#include "../../supports/matrix/src/Vectors.h"
//baseclass for the animal


class State;



const float TiredThreshold = 7.00;
const float Full  = 7.00;


class Animal
{
   protected:
      Vector3 pos;
      int id;
      int dir;
      int entity_id;
      float tiredLevel;
      float hunger;
      int score;
      State* currentState;
   public:
      Animal();
      Animal(int i);
      ~Animal();
      float getPositionX();
      float getPositionY();
      float getPositionZ();
      Vector3 getPosition();
      float getTiredLevel();
      int   getScore();
      float getHungerLevel();
      int   getId();
      int   getMovingDirection();
      
      void  setOppositeDirection();
      void  setMovingDirection(int new_dir);
      void  setPosition (Vector3 newPosition);
      void  setPositionX(float new_pos_x);
      void  setPositionY(float new_pos_y);
      void  setPositionZ(float new_pos_z);
      void  setPosition(float new_pos_x, float new_pos_y, float new_pos_z);
      void  drawBox();
      //the id is for collisiondetected
      int   generateRandom(int start, int end);
      void  patrol(int dir, int collide);

      void  decreaseFatigue();
      void  increaseFatigue();
      void  update();
      void  changeState(State* new_state);
      bool  tired()const;

      void  move(int dir);
      void  moveRight();
      void  moveLeft();
      void  moveUp();
      void  moveDown();
      void  stop();
      virtual void render(){};
      

};

#endif
