#include "gameController.h"
#include "../include/matrix/src/Vectors.h"
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
    px = theGameModel->getPosition_x();
    py = theGameModel->getPosition_y();
    pz = theGameModel->getPosition_z();
    lx = theGameModel->getLPosition_x();
    ly = theGameModel->getLPosition_y();
    lz = theGameModel->getLPosition_z();
    angle = theGameModel->getAngle();
    deltaAngle = theGameModel->getDeltaAngle();
    deltaMove = theGameModel ->getDeltaMove();
}


void GameController::keyboard(unsigned char key, int x, int y){
    getModelCameraSetting();
    Vector3 p (px,py,pz);
    Vector3 l (lx,ly,lz);
    Vector3 v;
    switch(key){
        case 'w':
            
             v.set(0,1,0);
	     p = p + v*0.1;
	     l = l + v*0.1;
             theGameModel->setPosition_x(p.x);
             theGameModel->setPosition_y(p.y);
             theGameModel->setPosition_z(p.z);
             theGameModel->setLPosition_x(l.x);
             theGameModel->setLPosition_y(l.y);
             theGameModel->setLPosition_z(l.z);
             theGameModel->setCameraPos(p.x,p.y,p.z);
             theGameModel->setCameraLookAtPos(l.x,l.y,l.z);
             break;
         case 's': //look down
             v.set(0,1,0);
	     p = p - v*0.1;
	     l = l - v*0.1;
	     theGameModel->setPosition_x(p.x);
             theGameModel->setPosition_y(p.y);
             theGameModel->setPosition_z(p.z);
             theGameModel->setLPosition_x(l.x);
             theGameModel->setLPosition_y(l.y);
             theGameModel->setLPosition_z(l.z);
             theGameModel->setCameraPos(p.x,p.y,p.z);
             theGameModel->setCameraLookAtPos(l.x,l.y,l.z);
             break;    
         case 'd': 
	     px += 0.1;
	      theGameModel->setPosition_x(px);
	      theGameModel->setCameraPos(p.x,p.y,p.z);
             theGameModel->setCameraLookAtPos(l.x,l.y,l.z);
	     break;    
         case 'a': 
	      px -= 0.1;
	      theGameModel->setPosition_x(px);
	      theGameModel->setCameraPos(p.x,p.y,p.z);
              theGameModel->setCameraLookAtPos(l.x,l.y,l.z);
	      break;
             
             
        case 27: //escape
              exit(0);
          break;

    }
}

void GameController::computePos(float newDeltaMove)
{
        getModelCameraSetting();
         Vector3 p (px,py,pz);
         Vector3 l (lx,ly,lz);
        p.x+=deltaMove*l.x*0.1;
        p.z+=deltaMove*l.z*0.1;
        theGameModel->setPosition_x(p.x);
        theGameModel->setPosition_z(p.z);
        theGameModel->setCameraPos(p.x,p.y,p.z);
        theGameModel->setCameraLookAtPos(l.x,l.y,l.z);
        
}

void GameController::computeDir(float newDeltaAngle)
{
        getModelCameraSetting();
        Vector3 l (lx,ly,lz);
        angle += deltaAngle;
	l.x = sin(angle);
	l.z = -cos(angle);
	theGameModel->setAngle(angle);
	theGameModel->setLPosition_x(l.x);
	theGameModel->setLPosition_z(l.z);
	theGameModel->setCameraLookAtPos(l.x,l.y,l.z);
	
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
