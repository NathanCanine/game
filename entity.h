#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

struct Point{
    int x=0;
    int y=0;
    int type = 0;
};

struct Projection{
    Point points[25] ;
    int length=0;
};

class Entity
{
private:
  int id;
  struct Projection *projection;
  struct Point *points;
  bool projected;
public:
  int interactions;
  bool resolved;
  bool resolve();
  void reset();
  int entity_type = -1;
  Entity();
  void interact();
  void act(Entity** locals, int local_pop, Entity** projectors, int projecting);
  int place(Entity** locals, int local_pop, Entity** projectors, int projecting);
  Projection project();
  int num_projection();
  void plan();
  int get_id();
  void set_id(int i);
};
#endif // ENTITY_H_INCLUDED
