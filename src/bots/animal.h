#ifndef ANIMAL_H
#define ANIMAL_H
#include <GL/glut.h>
#include <vector>
#include "../../supports/matrix/src/Vectors.h"
//baseclass for the animal


class State;



const float TiredThreshold = 24.00;
const float Full  = 7.00;
const float HungerThreshold = 7.00;
const float BoredThreshold  = 3.50;

class Animal
{
   protected:
      Vector3 pos;
      int id;
      int dir;
      int entity_id;
      float boredLevel;
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
      int   getEntityId();
      int   getMovingDirection();
      
      void  setBoredLevel(int level);
      void  setEntityId(int e_id);
      void  setOppositeDirection();
      void  setMovingDirection(int new_dir);
      void  setPosition (Vector3 newPosition);
      void  setPositionX(float new_pos_x);
      void  setPositionY(float new_pos_y);
      void  setPositionZ(float new_pos_z);
      void  setPosition(float new_pos_x, float new_pos_y, float new_pos_z);
      void  drawBox();
      
      //tired states
      bool  tired()const;
      bool  bored()const;
      void  decreaseFatigue();
      void  increaseFatigue();

      //update the ai
      void  update();
      void  changeState(State* new_state);
      
      //methods for moving
      void  patrol();
      void  changeDirection();
      void  move(int dir);
      void  moveRight();
      void  moveLeft();
      void  moveUp();
      void  moveDown();
      void  stop();

      int   generateRandom(int start, int end);

      virtual void render(){};
      

};

#endif
