#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "camera/camera.h"
#include "tileMap/tileMap.h"
#include <vector>
#include "../include/matrix/src/Vectors.h"
#include "bots/animal.h"
#include "bots/cat.h"
#include "bots/mouse.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

#include <cmath>
#include <cstdlib>
#include <pthread.h>
#include <cstring>
#include <sstream>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>       // Used for domain/DNS hostname lookup
#include <errno.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <cassert>
using namespace std;

#define PORT "3490"  // the port users will be connecting to

#define BACKLOG 10     // how many pending connections queue will hold

#define NUMCLIENT 2    //2 machines connect to the server.


class GameModel
{
   public:
   //Constructor
   GameModel(Camera *newCamera, TileMap *newTileMap);
   ~GameModel();
   //getters
   int getWindowWidth();
   int getWindowHeight();
   float getPosition_x();
   float getPosition_y();
   float getPosition_z();
   float getLPosition_x();
   float getLPosition_y();
   float getLPosition_z();
   float getAngle();
   float getDeltaAngle();
   float getDeltaMove();
   //get Camera variables to store in private
   float getCameraPos_x();
   float getCameraPos_y();
   float getCameraPos_z();
   void  getCameraPos();
   float getCameraLookAtPos_x();
   float getCameraLookAtPos_y();
   float getCameraLookAtPos_z();
   void  getCameraLookAtPos();
   float getCameraAngle();
   int   getNumOfAnimals();
   int   getNumOfCats();
   int   getNumOfCatsOne();
   int   getNumOfCatsTwo();
   int   getNumOfMice();
   int   getNumOfMiceOne();
   int   getNumOfMiceTwo();
   int   getNumOfMiceEaten();
   int   getNumOfCatAteMice();
   void getWallsPos();
   void getCheesePos();
   void getTileSettings();
   int  generateRandom(int start, int end);
   vector<Cat> getCats();
   vector<Cat> getCatsOne();
   vector<Cat> getCatsTwo();
   vector<Mouse> getMiceOne();
   vector<Mouse> getMiceTwo();
   vector<Mouse> getMice();
   vector<int>   getMiceEaten();
   vector<int>   getCatAteMiceVector();
   vector<int>   getMiceAteCheese();
   
   // setters
   void setPosition_x(float new_x);
   void setPosition_y(float new_y);
   void setPosition_z(float new_z);
   void setLPosition_x(float newLookAt_x);
   void setLPosition_y(float newLookAt_y);
   void setLPosition_z(float newLookAt_z);
   void setAngle(float newAngle);
   void setWindowResolution(int new_width, int new_height);
   void setCameraPos(float new_x, float new_y, float new_z);
   void setCameraLookAtPos(float newLookAt_x, float newLookAt_y, float newLookAt_z);
   void setCameraAngle(float newAngle);
   void setDeltaAngle(float dAngle);
   void setDeltaMove (float move);
  
   //gameSetting
   //void setBots();
   void initCamera();
   void initAnimals();
   void initCnM();
   
   void gameSetUp();
   void drawTile();
   void drawBots();
   void drawCats();
   void drawMouse();
   void drawCheese();
   void catCollideWalls(vector<Vector3>& walls, vector<Cat>& cats);
   void mouseCollideWalls(vector<Vector3>& walls,vector<Mouse>& mice);
   void catCollideCats(vector<Cat>& cats);
   void mouseCollideMice(vector<Mouse>& mice);
   void catsCaughtMice(vector<Cat>& cats, vector<Mouse>& mice);
   void mouseAteCheese(vector<Vector3>& cheese, vector<Mouse>& mice);
   bool testCollision(Vector3& a, Vector3& b, float width);
   void runCollision();
   void increaseClient();
   void splitAnimals();
   
   //networks 
   //sockets methods
   //create a thread for server accept.
   //server accept()
   //spawn a thread for a connection.
   //it shud be non-blocking.
   //thread
   void  createThreads();
   void  setInstance(); //to handle the static class.
   static void *serverHandler(void *);
   static void *clientHandler(void *socket);
   //create static functions for the thread to get something from the model to pass to client.
   static int getAnimalSize();
   static int getCatsSize();
   static int getCatsOneSize();
   static int getCatsTwoSize();
   static int getMiceSize();
   static int getMiceOneSize();
   static int getMiceTwoSize();
   static int getMiceEatenSize();
   static int getCatAteMiceSize();
   //needa send information to clients
   static vector<Cat> getCatsForClient();
   static vector<Cat> getCatsOneForClient();
   static vector<Cat> getCatsTwoForClient();
   static vector<Mouse> getMiceForClient();
   static vector<Mouse> getMiceOneForClient();
   static vector<Mouse> getMiceTwoForClient();
   static vector<int>  getMiceEatenForClient();
   static vector<int>  getCatAteMiceForClient();
   static vector<int>  getMiceAteCheeseForClient();
   static void         setStatesFromResults();
   static void doAiCalculation(int id);
   static void  registerClient();

   //since graphics rendering depends on the data in the model.
   //so the returned data from sockets can directly alter the data.
   
   

   private:
   
   static GameModel *instanceModel;
   int width, height;
   int client;
   float position_x, position_y, position_z; //for the camera
   float lposition_x, lposition_y, lposition_z; //for the camera lookAt
   float angle;//for camera angle
   float deltaAngle,deltaMove;
   float tileWidth, tileHeight;
   Camera *theCamera;
   TileMap *tile;
   vector <Vector3> wallsPos;
   vector <Vector3> cheesePos;
   vector <Animal>  animals;
   vector <Cat>     cats;
   vector <Cat>     cats_one;
   vector <Cat>     cats_two;
   vector <Mouse>   mice;
   vector <Mouse>   mice_one;
   vector <Mouse>   mice_two;
   
   vector <int>     miceEatenId;
   vector <int>     catAteMice;
   vector <int>     miceAteCheese;
   Cat c;
   Mouse m;
   
  //this is to store results get from client
  int testForClient;



   
};
#endif
