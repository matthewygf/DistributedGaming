#ifndef CAT_H
#define CAT_H
#include <GL/glut.h>
#include "animal.h"

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

