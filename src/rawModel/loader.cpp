
#define GL_GLEXT_PROTOTYPES
#include "loader.h"
#include <GL/glut.h>
#include "../../supports/glext.h"
#define N_ELEMENTS(array) (sizeof(array)/sizeof((array)[0])) 
#include <vector>

using namespace std;
RawModel Loader::loadToVao(vector<float>& positions)
{
   int vaoID = createVAO();
   storeData(0,positions);
   unbindVAO();
   int verticesCount = positions.size() / 3;
   RawModel rm(vaoID,verticesCount);
   return rm;
}

int Loader::createVAO()
{
  GLuint vao;
  glGenVertexArrays(1, &vao);
  int vaoID = vao;
  vaos.push_back(vaoID);
  glBindVertexArray(vaoID);
  return vaoID;
}

void Loader::storeData(int attributeNum, vector<float>& data)
{
   GLuint vbo;
   glGenBuffers(1, &vbo);
   int vboID = vbo;
   vbos.push_back(vboID);
   glBindBuffer(GL_ARRAY_BUFFER,vboID); 
   glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float),
   &data.front(),GL_STATIC_DRAW);
   glVertexAttribPointer(attributeNum,3,GL_FLOAT,GL_FALSE,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Loader::unbindVAO()
{
   glBindVertexArray(0);
}

void Loader::cleanUp()
{
  //need to implement deletearrays  

}


