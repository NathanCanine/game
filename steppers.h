#ifndef STEPPERS_H_INCLUDED
#define STEPPERS_H_INCLUDED
#include "entity.h"

void CopyGrid (bool **grid,bool **grid2, int x, int y);
void step(Tile **grid,int x, int y);
void liveOrDieCool(bool **grid,int x, int y);
Tile** initialize_grid(int x, int y,int mod);
void set_birth_ranges(int *birth_ranges_arg, int length);
void set_die_ranges(int *birth_ranges_arg, int length);

#endif // STEPPERS_H_INCLUDED
