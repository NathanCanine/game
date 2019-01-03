#include "entity.h"

Entity::Entity(int x,int y)
{
  xpos = x;
  ypos = y;
}

int Entity::getSum()
{
  return xpos + ypos;
}

Tile::Tile(bool is_grassy)
{
  grassy = is_grassy;
}

void Tile::setGrassy(bool is_grassy){
    grassy = is_grassy;
}


void Tile::setNextGrassy(bool will_grassy){
    next_grassy = will_grassy;
}

bool Tile::getGrassy(){
  return grassy;
}
