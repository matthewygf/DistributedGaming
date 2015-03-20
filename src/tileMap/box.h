#ifndef BOX_H
#define BOX_H
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "../../supports/matrix/src/Vectors.h"

using namespace std;
class Box
{
  public:
  Box();
  ~Box();
  void render();
  Vector3 getPoint();

  private:
  Vector3 velocity;
  Vector3 pos;
  float w;//width
  Vector3 color;

};

#endif
