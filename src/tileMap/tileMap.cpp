#include "tileMap.h"
#include "../../include/stb_image.h"
#include <stdio.h>
#include <iostream>

#include <vector>
#include "../../include/matrix/src/Vectors.h"
using namespace std;

TileMap::TileMap(int mapSize_x,int mapSize_y,
                  const char *texture_one,const char *texture_two)
{

    x_size = mapSize_x;
    y_size = mapSize_y;
   //set to private
    setMap();
    setWalls();
    setCheese();
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

    int result = start + (rand() % (int)(end - start + 1));
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


void TileMap::setWalls()
{
   for(int i = 0; i<y_size ; i++){
        int y = generateRandom(0 , y_size-1);
   	int x = generateRandom(0 , x_size-1);   
        if(m[y][x] == 0){
   	m[y][x] = 1;
	}
   }
}

void TileMap::setCheese()
{
  for(int i = 0; i<y_size; i++){
   int y = generateRandom(0,y_size-1);
   int x = generateRandom(0,x_size-1);
   if(m[y][x]==0 && m[y][x]!=1){
     m[y][x]=2;
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

void TileMap::calculateWallsPos()
{
 int tile;
 for (int y = 0 ; y < y_size; y++)
   {
     for(int x = 0; x < x_size; x++)
     {
       tile = m[y][x];
       if(tile==1){
       Vector3 wallPos(x+0.5,y-2.5,0.5);
       wallsPos.push_back(wallPos);
       }
     }
   }
}

void TileMap::calculateCheesePos()
{
 int tile;
 for (int y = 0 ; y < y_size; y++)
   {
     for(int x = 0; x < x_size; x++)
     {
       tile = m[y][x];
       if(tile==2){
       Vector3 cheese(x+0.5,y-2.5,0.5);
       cheesePos.push_back(cheese);
       }
     }
   }
}

vector <Vector3> TileMap::getCheesePos()
{
  calculateCheesePos();
  return cheesePos;
}


vector <Vector3> TileMap::getWallsPos()
{
  calculateWallsPos();
  return wallsPos;
}

void TileMap::drawWalls()
{
  for(unsigned int i = 0; i<wallsPos.size();i++)
  {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturesID[1]);
    glTranslatef(wallsPos[i].x,wallsPos[i].y,wallsPos[i].z);

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

}

void TileMap::drawCheese()
{
  //cout<<"cheese drawing and cheese sizes are : "<<cheesePos.size()<<endl;
  for(unsigned int i = 0; i<cheesePos.size();i++)
  {
    glPushMatrix();
   
    glTranslatef(cheesePos[i].x,cheesePos[i].y,cheesePos[i].z);
    
    glColor3f(1.0,1.0,0.0);
    cheese();

    glPopMatrix();
  }
}

void TileMap::render()
{
   //walls
   drawWalls();

   
   //floor
   for (int y = 0 ; y < y_size; y++)
   {
     for(int x = 0; x < x_size; x++)
     {
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
 //cheese
   //drawCheese();
}

void TileMap::cheese()
{
          glBegin(GL_TRIANGLES);
           glVertex3f(-1.0/4,-1.0/4,-1.0/4); // triangle 1 : begin
           glVertex3f(-1.0/4,-1.0/4, 1.0/4);
           glVertex3f(-1.0/4, 1.0/4, 1.0/4); // triangle 1 : end
 
           glVertex3f(1.0/4, 1.0/4,-1.0/4); // triangle 2 : begin
           glVertex3f(-1.0/4,-1.0/4,-1.0/4);
           glVertex3f(-1.0/4, 1.0/4,-1.0/4); // triangle 2 : end
 
           glVertex3f(1.0/4,-1.0/4, 1.0/4); // triangle 3 :begin
           glVertex3f(-1.0/4,-1.0/4,-1.0/4);
           glVertex3f(1.0/4,-1.0/4,-1.0/4);  //triangle 3 :end
 
           glVertex3f(1.0/4, 1.0/4,-1.0/4); // triangle 4 :begin
           glVertex3f(1.0/4,-1.0/4,-1.0/4);
           glVertex3f(-1.0/4,-1.0/4,-1.0/4);// triangle 4 :end
 
           glVertex3f(-1.0/4,-1.0/4,-1.0/4); //triangle 5 :begin
           glVertex3f(-1.0/4, 1.0/4, 1.0/4);
           glVertex3f(-1.0/4, 1.0/4,-1.0/4); // triangle 5 :end
 
           glVertex3f(1.0/4,-1.0/4, 1.0/4); //triangle 6 :begin
           glVertex3f(-1.0/4,-1.0/4, 1.0/4);
           glVertex3f(-1.0/4,-1.0/4,-1.0/4); //triangle 6 :end
 
           glVertex3f(-1.0/4, 1.0/4, 1.0/4); //triangle 7 :begin
           glVertex3f(-1.0/4,-1.0/4, 1.0/4);
           glVertex3f(1.0/4,-1.0/4, 1.0/4); //triangle 7 :end
 
           glVertex3f(1.0/4, 1.0/4, 1.0/4); //triangle 8 :begin
           glVertex3f(1.0/4,-1.0/4,-1.0/4);
           glVertex3f(1.0/4, 1.0/4,-1.0/4); //triangle 8 :end
 
           glVertex3f(1.0/4,-1.0/4,-1.0/4); //triangle 9 :begin
           glVertex3f(1.0/4, 1.0/4, 1.0/4);
           glVertex3f(1.0/4,-1.0/4, 1.0/4); //triangle 9 :end
 
           glVertex3f(1.0/4, 1.0/4, 1.0/4); //triangle 10 :begin
           glVertex3f(1.0/4, 1.0/4,-1.0/4);
           glVertex3f(-1.0/4, 1.0/4,-1.0/4); //triangle 10 :end
 
           glVertex3f(1.0/4, 1.0/4, 1.0/4); //triangle 11 :begin
           glVertex3f(-1.0/4, 1.0/4,-1.0/4);
           glVertex3f(-1.0/4, 1.0/4, 1.0/4); //triangle 11 :end
 
           glVertex3f(1.0/4, 1.0/4, 1.0/4);//triangle 12 :begin
           glVertex3f(-1.0/4, 1.0/4, 1.0/4);
           glVertex3f(1.0/4,-1.0/4, 1.0/4); //triangle 12 :end
        glEnd();
}



