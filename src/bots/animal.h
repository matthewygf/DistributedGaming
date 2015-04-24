#ifndef ANIMAL_H
#define ANIMAL_H
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include "../../include/matrix/src/Vectors.h"
//baseclass for the animal

using namespace std;
class State;

const float TiredThreshold = 24.00;
const float Full  = 7.00;
const float HungerThreshold = 7.00;
const float BoredThreshold  = 3.50;

class Animal
{
   protected:
      Vector3 pos;
      vector <int> objectsBumped;
      int id;
      int dir;
      int entity_id;
      float speed;
      float boredLevel;
      float tiredLevel;
      float hunger;
      int score;
      int state;
      int mapSize;
      State* currentState;
   public:
      Animal();
      Animal(int i);
      ~Animal();

      float getSpeed();
      float getPositionX();
      float getPositionY();
      float getPositionZ();
      Vector3 getPosition();
      float getTiredLevel();
      int   getScore();
      float getHungerLevel();
      int   getId();
      int   getEntityId();
      int   getState();
      int   getMovingDirection();
      int   getCurrentState();
      int   getMapSize();
      
      void  goToState();
      void  setState(int new_state);
      void  setMapSize(int new_mapSize);
      void  setSpeed(float newSpeed);
      void  setScore(int newScore);
      void  setBoredLevel(int level);
      void  setCurrentState(int state);
      void  setHungerLevel(float newHunger);
      void  setEntityId(int e_id);
      void  setOppositeDirection();
      void  setMovingDirection(int new_dir);
      void  setPosition (Vector3 newPosition);
      void  setPositionX(float new_pos_x);
      void  setPositionY(float new_pos_y);
      void  setPositionZ(float new_pos_z);
      void  setPosition(float new_pos_x, float new_pos_y, float new_pos_z);
      void  drawBox();
      
      // states methods
      bool  tired()const;
      bool  bored()const;
      bool  hungry()const;
      void  decreaseFatigue();
      void  increaseFatigue();
      void  increaseHunger();
      void  decreaseHunger();
      void  calculatePrimeNumbers();

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
