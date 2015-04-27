
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "gameModel.h"

class GameController
{
   public:
      GameController(GameModel *newGameModel);

      virtual~GameController();

      virtual void keyboard(unsigned char key, int x, int y);
      virtual void specialInput(int key, int x, int y);
      virtual void specialFunctionInput(int key, int x, int y);
   
   //select bots;
   void getModelCameraSetting();
   void computePos(float newDeltaMove);
   void computeDir(float newDeltaAngle);
      
   private:
   GameModel *theGameModel;
   
   //camera variables
   float px, py, pz,
         lx, ly, lz,
          angle, deltaAngle, deltaMove;
  
   


};
#endif
