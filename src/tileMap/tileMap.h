#ifndef TILEMAP_H
#define TILEMAP_H
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "../../supports/matrix/src/Vectors.h"
#include "box.h"

class TileMap
{
   public:
   TileMap(int mapSize_x, int mapSize_y,
                 const char *texture_one, const char *texture_two);
   ~TileMap();
 
   //return the map array to theGameModel.
   void setMap();
   void setWalls();
   int  getWidth();
   int  getHeight();
   void initTexture();
   void loadTexture(GLuint texture, const char* filename);
   void render();
   void drawBox();
   void drawWalls();
   int generateRandom(int start, int end);
   void calculateWallsPos();
   vector <Vector3> getWallsPos();
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
   const static GLsizei textureSize = 2;
   vector <Vector3> wallsPos;

   GLuint texturesID[textureSize]; //only 2 textures
   

   
};
#endif

