#ifndef TILEMAP_H
#define TILEMAP_H
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include <GL/glut.h>
#include <iostream>

class TileMap
{
   public:
   TileMap(int mapSize_x, int mapSize_y,
                 const char *texture_one, const char *texture_two);
   ~TileMap();
 
   //return the map array to theGameModel.
   void setMap();
   void initTexture();
   void loadTexture(GLuint texture, const char* filename);
   void render();
   void drawBox();

   private:
   int x_size;
   int y_size;
   const char *textureOne;
   const char *textureTwo;
   int **m;
   const int *mdata;
   const static GLsizei textureSize = 2;
   GLuint texturesID[textureSize]; //only 2 textures
   

   
};
#endif

