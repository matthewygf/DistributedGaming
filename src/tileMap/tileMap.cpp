#include "tileMap.h"
#include "../../supports/stb_image.h"
#include <stdio.h>
#include <iostream>
#include <random>
#include <vector>
#include "../../supports/matrix/src/Vectors.h"
using namespace std;

TileMap::TileMap(int mapSize_x,int mapSize_y,
                  const char *texture_one,const char *texture_two)
{

    x_size = mapSize_x;
    y_size = mapSize_y;
   //set to private

    setMap();
    setWalls();
    textureOne = texture_one;
    textureTwo = texture_two;
}

TileMap::~TileMap()
{
  
  for (  int i = 0; i < y_size; i++)
    {
      delete [] m[i]; 
     }
  delete [] m;
  delete mdata;
  delete textureOne;
  delete textureTwo;
}

int TileMap::getWidth()
{
   return y_size;
}

int TileMap::getHeight()
{
   return x_size;
}

int TileMap::generateRandom(int start, int end)
{

    random_device                  rand_dev;
    mt19937                        generator(rand_dev());
    uniform_int_distribution<int>  distr(start, end);
    
    int result = distr(generator);
    return result;
    
}


void TileMap::setMap()
{
    m = new int*[y_size];
    for (int i = 0; i<y_size; i++){
       m[i] = new int[x_size];
        for (int j = 0; j<x_size; j++) {
            if (i == 0 || i == y_size-1 || j== 0 || j == x_size -1)         {
                m[i][j]= 1;

            } else {
		
                m[i][j]=0;
            }
        }
    }

}

int TileMap::isWall(int i, int j)
{
   if (m[i][j] == 1){
      return 1;
   } else {
      return 0;
   }
}

void TileMap::setWalls()
{
   for(int i = 0; i<y_size*2 ; i++){
        int y = generateRandom(0 , y_size);
   	int x = generateRandom(0 , x_size);   
        if(m[y][x] != 1){
   	m[y][x] = 1;
	}
   }

}

 void TileMap::initTexture()
{
    glGenTextures(textureSize,texturesID);
    loadTexture(texturesID[0], textureOne);
    loadTexture(texturesID[1], textureTwo);
}

void TileMap::loadTexture(GLuint texture, const char* filename)
{
    int x;
    int y;
    int n;
    //loading in the pictures
    //cout<<filename<<endl;
   unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
   if (data == NULL) {
        cout << "Error, can not find the image, please check your path at initTextures()"<<endl;
   } else {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //clamping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        /* Set texture mode */
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        /* Make sure we've got the right texture */

   }
   stbi_image_free(data);

}




void TileMap::render()
{
   
   int tile;
   vector <Vector3> wallsPos;
   for (int y = 0 ; y < y_size; y++)
   {
     for(int x = 0; x < x_size; x++)
     {
        tile = m[y][x];
        if(tile==1){
       // cout<<"going to draw a cube"<<endl;
          glPushMatrix();
          glEnable(GL_TEXTURE_2D);
          glBindTexture(GL_TEXTURE_2D, texturesID[1]);
          Vector3 wallPos(x+0.5,y-2.5,0.5);
          wallsPos.push_back(wallPos);

          glTranslatef(x+0.5,y-2.5,0.5);

          glBegin(GL_TRIANGLES);
         glTexCoord2f(0.0,1.0);    glVertex3f(-1.0/2,-1.0/2,-1.0/2); // triangle 1 : begin
         glTexCoord2f(1.0,0.0);    glVertex3f(-1.0/2,-1.0/2, 1.0/2);
         glTexCoord2f(0.0,0.0);    glVertex3f(-1.0/2, 1.0/2, 1.0/2); // triangle 1 : end
 
         glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2, 1.0/2,-1.0/2); // triangle 2 : begin
         glTexCoord2f(1.0,0.0);     glVertex3f(-1.0/2,-1.0/2,-1.0/2);
         glTexCoord2f(0.0,0.0);     glVertex3f(-1.0/2, 1.0/2,-1.0/2); // triangle 2 : end
 
         glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2,-1.0/2, 1.0/2); // triangle 3 :begin
         glTexCoord2f(1.0,0.0);     glVertex3f(-1.0/2,-1.0/2,-1.0/2);
         glTexCoord2f(0.0,0.0);     glVertex3f(1.0/2,-1.0/2,-1.0/2);  //triangle 3 :end
 
         glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2, 1.0/2,-1.0/2); // triangle 4 :begin
         glTexCoord2f(1.0,0.0);     glVertex3f(1.0/2,-1.0/2,-1.0/2);
         glTexCoord2f(0.0,0.0);      glVertex3f(-1.0/2,-1.0/2,-1.0/2);// triangle 4 :end
 
        glTexCoord2f(0.0,1.0);     glVertex3f(-1.0/2,-1.0/2,-1.0/2); //triangle 5 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(-1.0/2, 1.0/2, 1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(-1.0/2, 1.0/2,-1.0/2); // triangle 5 :end
 
        glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 6 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(-1.0/2,-1.0/2, 1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(-1.0/2,-1.0/2,-1.0/2); //triangle 6 :end
 
        glTexCoord2f(0.0,1.0);     glVertex3f(-1.0/2, 1.0/2, 1.0/2); //triangle 7 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(-1.0/2,-1.0/2, 1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 7 :end
 
        glTexCoord2f(0.0,1.0);      glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 8 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(1.0/2,-1.0/2,-1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(1.0/2, 1.0/2,-1.0/2); //triangle 8 :end
 
        glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2,-1.0/2,-1.0/2); //triangle 9 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(1.0/2, 1.0/2, 1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 9 :end
 
        glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 10 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(1.0/2, 1.0/2,-1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(-1.0/2, 1.0/2,-1.0/2); //triangle 10 :end
 
        glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 11 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(-1.0/2, 1.0/2,-1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(-1.0/2, 1.0/2, 1.0/2); //triangle 11 :end
 
        glTexCoord2f(0.0,1.0);     glVertex3f(1.0/2, 1.0/2, 1.0/2);//triangle 12 :begin
        glTexCoord2f(1.0,0.0);     glVertex3f(-1.0/2, 1.0/2, 1.0/2);
        glTexCoord2f(0.0,0.0);     glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 12 :end
        glEnd();
        glPopMatrix();
        }
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, texturesID[0]);
        glBegin(GL_QUADS);
        //each tile have a x n y coordinate of 1 apart
        glTexCoord2f(0.0f, 0.0f); glVertex3f(float(x), float(y-3), 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(float(x + 1), float(y-3), 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(float(x + 1), float(y -2), 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(float(x), float(y -2), 0.0f);
        glEnd();
        }
     
   }
   
   glDisable(GL_TEXTURE_2D);
}



