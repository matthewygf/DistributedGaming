#include "gameController.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
GameController::GameController(GameModel *newGameModel)
{
    theGameModel = newGameModel;
    cout<<"controllerInitialised"<<endl;
}

GameController::~GameController()
{
  delete theGameModel;
  cout<<"deleting Model within Controller"<<endl;
}

void GameController::getModelCameraSetting(){
    x = theGameModel->getPosition_x();
    y = theGameModel->getPosition_y();
    z = theGameModel->getPosition_z();
    lx = theGameModel->getLPosition_x();
    ly = theGameModel->getLPosition_y();
    lz = theGameModel->getLPosition_z();
    angle = theGameModel->getAngle();
    deltaAngle = theGameModel->getDeltaAngle();
    deltaMove = theGameModel ->getDeltaMove();
}


void GameController::keyboard(unsigned char key, int x, int y){
    getModelCameraSetting();
    switch(key){
        case 'w': //look up
             ly += 0.01;
             theGameModel->setLPosition_y(ly);
             break;
         case 's': //look down
             ly -= 0.01;
             theGameModel->setLPosition_y(ly);
             break;    
        case 27: //escape
              exit(0);
          break;

    }
}

void GameController::computePos(float newDeltaMove)
{
        getModelCameraSetting();
        x+=deltaMove*lx*0.1;
        z+=deltaMove*lz*0.1;
        theGameModel->setPosition_x(x);
        theGameModel->setPosition_z(z);
}

void GameController::computeDir(float newDeltaAngle)
{
        getModelCameraSetting();
        angle += deltaAngle;
	lx = sin(angle);
	lz = -cos(angle);
	theGameModel->setAngle(angle);
	theGameModel->setLPosition_x(lx);
	theGameModel->setLPosition_z(lz);
	
}



void GameController::specialFunctionInput(int key, int xx, int yy) {
   getModelCameraSetting();

      switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : theGameModel->setDeltaAngle(0);break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : theGameModel->setDeltaMove(0);break;
	}
   
}

void GameController::specialInput(int key, int xx, int yy) {
        getModelCameraSetting();
	switch (key) {
		case GLUT_KEY_LEFT : theGameModel->setDeltaAngle(-0.01f); break;
		case GLUT_KEY_RIGHT : theGameModel->setDeltaAngle(0.01f); break;
		case GLUT_KEY_UP : theGameModel->setDeltaMove(0.5); break;
		case GLUT_KEY_DOWN : theGameModel->setDeltaMove(-0.5); break;
	}
}
