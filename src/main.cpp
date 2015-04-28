
#include "gameModel.h"
#include "gameView.h"
#include "gameController.h"
#include "camera/camera.h"
#include "tileMap/tileMap.h"
#include "../include/vbo/src/Timer.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>



#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define MAP_SIZEX 40
#define MAP_SIZEY 40
//also need to set in gameModel.h and animalStates.cpp
//#define singleThreaded true

// angle of rotation for the camera direction
float ang=0.0;
// actual vector representing the camera's lookat direction
float lx=0.0f,ly=1.1,lz=-1.0f;
// XYZ position of the camera
float px=15.0f,py=1.0f,pz=14.0f;
//near plane, far plane, and Field Of View
float near = 0.1f,far=100.f,FOV=60.0f;

const char *texture_one = "data/grass.jpeg";
const char *texture_two = "data/wood.jpeg";



void GameLoop(GameView *view,int argc, char *argv[]){
       view->render(argc, argv); //this is the graphics main loop
}

int main(int argc, char **argv)
{

   Camera *camera = new Camera(px,py,pz+5,lx,ly,lz,ang,near,far,FOV);

   TileMap *tmap = new TileMap(MAP_SIZEY,MAP_SIZEX,texture_one,texture_two,camera);
   
   
   //model-view-controller
   
   GameModel *model = new GameModel(camera,tmap);
   //start server.
   if(!singleThreaded){
   model->createThreads(); //comment out for running on local machine
   }
   //controller modifed the model.
   GameController *controller = new GameController(model);

   //View 
   GameView *view = new GameView(controller,model);
   GameLoop(view,argc,argv); // will also contain physics, AI



    delete camera;
    delete model;
    delete view;
    delete controller;
    delete tmap;

   
   return 0;
 
}
