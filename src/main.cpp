
#include "gameModel.h"
#include "gameView.h"
#include "gameController.h"
#include "camera/camera.h"
#include "tileMap/tileMap.h"
#include <pthread.h>
#include <iostream>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>

#endif



#define MAP_SIZEX 10
#define MAP_SIZEY 10




// angle of rotation for the camera direction
float ang=0.0;
// actual vector representing the camera's lookat direction
float lx=0.0f,ly=1.1,lz=-1.0f;
// XYZ position of the camera
float px=5.0f,py=1.0f,pz=14.0f;

int map[MAP_SIZEY*MAP_SIZEX] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

const char *texture_one = "data/grass.jpeg";
const char *texture_two = "data/wood.jpeg";




void GameLoop(GameView *view,int argc, char *argv[]){
       view->render(argc, argv);
}




int main(int argc, char **argv)
{


   TileMap *tmap = new TileMap(MAP_SIZEY,MAP_SIZEX,map,texture_one,texture_two);
   
   Camera *camera = new Camera(px,py,pz+5,lx,ly,lz,ang);
   //model-view-controller
   
   GameModel *model = new GameModel(camera,tmap);

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
