#include "cat.h"
#include <iostream>
using namespace std;

Cat::Cat()
{
}

Cat::~Cat()
{
}

void Cat::render()
{
  glColor3f(0.9,0.9,0.9);
  drawBox();
}

void Cat::caught()
{
  score += 1;
}

