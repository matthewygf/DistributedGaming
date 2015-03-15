#ifndef RAWMODEL_H
#define RAWMODEL_H
#include <GL/glut.h>


class RawModel
{
    public:
       RawModel(int new_vaoID, int new_vertexCount);
       int renderModel();
       int getVaoID();
       int getVertexCount();
       
       
       void test();
    
    
    private:    
      int vaoID;
      int vertexCount;
      
};

#endif
