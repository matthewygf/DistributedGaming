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



void GameController::specialInput(int key, int xx, int yy) {
        float step = 0.1;
        getModelCameraSetting();
	switch (key) {
		case GLUT_KEY_LEFT :
		        cout<<"LEFT"<<endl;
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			theGameModel->setAngle(angle);
			theGameModel->setLPosition_x(lx);
			theGameModel->setLPosition_z(lz);
			
			break;
		case GLUT_KEY_RIGHT :
		        cout<<"RIGHT"<<endl;
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			theGameModel->setAngle(angle);
			theGameModel->setLPosition_x(lx);
			theGameModel->setLPosition_z(lz);
			break;
		case GLUT_KEY_UP :
		        cout<<"UP"<<endl;
			x += lx * step;
	                z += lz * step;
	                theGameModel->setPosition_x(x);
      	                theGameModel->setPosition_z(z);
			break;
		case GLUT_KEY_DOWN :
		        cout<<"DOWN"<<endl;
		        x -= lx * step;
			z -= lz * step;
			theGameModel->setPosition_x(x);
      	                theGameModel->setPosition_z(z);
			break;
	}
}
