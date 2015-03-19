#ifndef MOUSE_H
#define MOUSE_H
#include <GL/glut.h>
#include "animal.h"

class Mouse:public Animal
{
  public:
   Mouse();
   ~Mouse();
   virtual void render();
};
#endif
