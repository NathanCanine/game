#ifndef STEPPERS_H_INCLUDED
#define STEPPERS_H_INCLUDED

void CopyGrid (bool **grid,bool **grid2, int x, int y);
void liveOrDie(bool **grid,int x, int y);
void liveOrDieCool(bool **grid,int x, int y);
bool** initialize_grid(int x, int y);

#endif // STEPPERS_H_INCLUDED
