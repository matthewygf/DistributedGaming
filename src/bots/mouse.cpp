#include "mouse.h"
#include <iostream>

using namespace std;

Mouse::Mouse()
{
  id = 0;
}

Mouse::~Mouse()
{
}

void Mouse::render()
{
   glColor3f(0.0,0.9,0.7);
   drawBox();
}

int Mouse::getId()
{
  return id;
}
