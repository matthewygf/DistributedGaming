#include "cat.h"
#include <iostream>
using namespace std;

Cat::Cat()
{
  id = 1;
}

Cat::~Cat()
{
}

void Cat::render()
{
  glColor3f(0.9,0.9,0.9);
  drawBox();
}

int Cat::getId()
{
  return id;
}
