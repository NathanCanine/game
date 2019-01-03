#include "entity.h"

Entity::Entity(int x,int y)
{
  xpos = x;
  ypos = y;
}

int Entity::getSum()
{
  return gx + gy;
}
