#ifndef CAT_H
#define CAT_H
#include "animal.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Cat:public Animal
{
  public:
    Cat();
    Cat(int i);
    ~Cat();
    virtual void render();
    int getId();
    void caught();
  private:
   int id;
};

#endif

