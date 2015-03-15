
#define GL_GLEXT_PROTOTYPES
#include "rawModel.h"
#include <GL/glut.h>
#include "../../supports/glext.h"
#include <iostream>
#define N_ELEMENTS(array) (sizeof(array)/sizeof((array)[0])) 

using namespace std;


RawModel::RawModel(int new_vaoID, int new_vertexCount)
{    
   vaoID = new_vaoID;
   vertexCount = new_vertexCount;
}

int RawModel::renderModel()
{
   GLfloat vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};   

   GLuint vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
   
   GLuint vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER,vbo); 
   glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_buffer_data),vertex_buffer_data,GL_STATIC_DRAW);
   cout<<sizeof(vertex_buffer_data)<<endl;
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
   
   glBindVertexArray(0);

   return vao;
}


int RawModel::getVaoID(){
    return vaoID;
}

int RawModel::getVertexCount(){
   return vertexCount;
}




