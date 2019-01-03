#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

class Entity
{
  int xpos = -1;
  int ypos = -1;
public:
  Entity(int x,int y);
  int getSum ();
};


class Tile
{
public:
  bool grassy = 0;
  bool next_grassy = 0;
  Tile(bool is_grassy);
  void setGrassy (bool is_grassy);
  void setNextGrassy(bool will_grassy);
  bool getGrassy ();
};

#endif // ENTITY_H_INCLUDED
