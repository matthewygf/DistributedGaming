#ifndef MOUSE_H
#define MOUSE_H
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "animal.h"

class Mouse:public Animal
{
  public:
   Mouse();
   Mouse(int i);
   ~Mouse();
   virtual void render();
   int getId();
   void ateCheese();
  private:
   int id;
};
#endif
