#ifndef CAT_H
#define CAT_H
#include <GL/glut.h>
#include "animal.h"

class Cat:public Animal
{
  public:
    Cat();
    ~Cat();
    virtual void render();
};

#endif

