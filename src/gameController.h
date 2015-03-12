
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <stdio.h>
#include <GL/glut.h>

#include "gameModel.h"

class GameController
{
   public:
      GameController(GameModel *newGameModel);

      virtual~GameController();

      //virtual void mouse(int button, int state, int x, int y);
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
   float x, y, z,
         lx, ly, lz,
          angle, deltaAngle, deltaMove;
   


};
#endif
