#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

class Tile
{
  Entity **entities;
  Entity **projecting;
public:
  bool completed = false;
  int population;
  int num_projecting;
  Tile();
  bool add_projecting(Entity *e);
  Entity **get_projecting();
  Entity **get_entities();
  Entity* remove_entity(int id);
  Entity* add_entity(Point p);
  void reset();
};

#endif
