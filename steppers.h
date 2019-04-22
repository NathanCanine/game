#ifndef STEPPERS_H_INCLUDED
#define STEPPERS_H_INCLUDED
#include "entity.h"
#include "tile.h"

void step();
Tile** initialize_grid(int x, int y,int mod);

#endif // STEPPERS_H_INCLUDED
