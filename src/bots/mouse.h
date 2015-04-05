#ifndef MOUSE_H
#define MOUSE_H
#include <GL/glut.h>
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
