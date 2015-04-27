#ifndef TILEMAP_H
#define TILEMAP_H
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <vector>
#include "../camera/camera.h"
#include "../../include/matrix/src/Vectors.h"
#include "box.h"

class TileMap
{
   public:
   TileMap(int mapSize_x, int mapSize_y,
                 const char *texture_one, const char *texture_two,Camera *cam);
   ~TileMap();
 
   //return the map array to theGameModel.
   void setMap();
   void setWalls();
   void setCheese();
   int  getWidth();
   int  getHeight();
   void initTexture();
   void loadTexture(GLuint texture, const char* filename);
   void render();
   void drawBox();
   void drawWalls();
   void drawCheese();
   void cheese();
   int generateRandom(int start, int end);
   void calculateWallsPos();
   void calculateCheesePos();
   bool calculateFrustum(Vector3 &p);
   vector <Vector3> getWallsPos();
   vector <Vector3> getCheesePos();
   //need to make a method for storing walls information
   //calculateWallsPosi & store walls vertices for collision
   //return the vector for the world
   //getwallsPos;

   private:
   int x_size;
   int y_size;
   const char *textureOne;
   const char *textureTwo;
   int **m;
   const int *mdata;
   Camera *theCam;
   const static GLsizei textureSize = 2;
   vector <Vector3> wallsPos;
   vector <Vector3> cheesePos;

   GLuint texturesID[textureSize]; //only 2 textures
   

   
};
#endif

