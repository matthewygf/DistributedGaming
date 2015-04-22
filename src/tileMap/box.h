#ifndef BOX_H
#define BOX_H
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include <iostream>
#include "../../include/matrix/src/Vectors.h"

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
