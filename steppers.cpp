#include <cstdlib>
#include "steppers.h"
#include <iostream>
#include <map>

struct EntityLocation {
    Entity* entity;
    int x;
    int y;
};

int entity_ids = 0;
Tile **game_grid;
int width =0;
int height =0;
int max_pop = 10000000;
EntityLocation **entity = (EntityLocation**)malloc(max_pop * sizeof(EntityLocation*));
int entity_population = 0;
void add_entity(Point p){
    if(entity_population>max_pop){
        return;
    }
    Entity *e = game_grid[p.x][p.y].add_entity(p);
    if(!e){
        return;
    }
    EntityLocation *pos = (EntityLocation*)malloc(sizeof(EntityLocation));
    pos->entity = e;
    pos->x = p.x;
    pos->y = p.y;
    entity[entity_population++] = pos;
}

void remove_entity(int i){
    EntityLocation *this_location = entity[i];
    Entity *e = this_location->entity;
    game_grid[this_location->x][this_location->y].remove_entity(e->get_id());
    delete e;
    delete this_location;
    //entity_population=entity_population-1;
    if(entity_population==1){
        entity_population=0;
        return;
    } else {
        entity[i] = entity[--entity_population];
        return;
    }
    return;
}


bool can_project(Point p, EntityLocation* l){
    if((p.x+l->x)>=width || (p.x +l->x) < 0 || (p.y+l->y)>=height || (p.y + l->y) <0){
        return false;
    }
    return true;
}

void project(){
    for(int a = 0; a < entity_population; a++){
        EntityLocation *this_location = entity[a];
        Entity *this_entity = this_location->entity;
        Projection points = this_entity->project();
        for(int i=0;i<points.length;i++){
            Point p = points.points[i];
            if(can_project(p,this_location)){
                Tile *t = &game_grid[this_location->x+p.x][this_location->y + p.y];
                game_grid[this_location->x+p.x][this_location->y + p.y].add_projecting(this_entity);
            }
        }
    }
}

void act(){
    for(int a = 0; a < entity_population; a++){
        EntityLocation *this_location = entity[a];
        Entity *this_entity = this_location->entity;
        Projection points = this_entity->project();
        for(int i=0;i<points.length;i++){
            Point p = points.points[i];
            if(can_project(p,this_location)){
                Tile t = game_grid[this_location->x+p.x][this_location->y + p.y];
                this_entity->act(t.get_entities(), t.population,t.get_projecting(),t.num_projecting);
            }
        }
    }
}

int place(Point* birth_tiles){
    int num_birth = 0;
    for(int a = 0; a < entity_population; a++){
        EntityLocation *this_location = entity[a];
        Entity *this_entity = this_location->entity;
        Projection points = this_entity->project();
        for(int i=0;i<points.length;i++){
            Point p = points.points[i];
            if(can_project(p,this_location)){
                Tile t = game_grid[this_location->x+p.x][this_location->y + p.y];
                int entity_type = this_entity->place(t.get_entities(), t.population,t.get_projecting(),t.num_projecting);
                if(entity_type>=0){
                    Point to_birth;
                    to_birth.x=(this_location->x+p.x);
                    to_birth.y=(this_location->y+p.y);
                    to_birth.type = entity_type;
                    birth_tiles[num_birth++] = to_birth;
                }
            }
        }
    }
}

void resolve(int num_birth, Point* birth_tiles){
    for(int a = 0; a < entity_population; a++){
        EntityLocation *this_location = entity[a];
        Entity *this_entity = this_location->entity;
        if(this_entity->resolve()){
            remove_entity(a--);
        }
    }
    for(int i=0;(i<(num_birth-1)) && (entity_population<max_pop);i++){
        Point born = birth_tiles[i];
        //std::cout<<"PUMP"<<born.x<<"  ::  "<<born.y<<"\n"<<std::flush;
        //std::cout<<"BUMP"<<i<<"  ::  "<<num_birth<<"\n"<<std::flush;
        Tile t = game_grid[born.x][born.y];
        add_entity(born);
    }
}

void reset(){
    for(int a = 0; a < entity_population; a++){
        EntityLocation *this_location = entity[a];
        Entity *this_entity = this_location->entity;
        this_entity->reset();
        Projection points = this_entity->project();
        for(int i=0;i<points.length;i++){
            Point p = points.points[i];
            if(can_project(p,this_location)){
                game_grid[this_location->x+p.x][this_location->y + p.y].reset();
            }
        }
    }
}

void step(){
    project();
    act();
    Point* birth_tiles=(Point*)malloc(16*max_pop*sizeof(Point));
    int birth = place(birth_tiles);
    resolve(birth, birth_tiles);
    free(birth_tiles);
    reset();
}


Tile** initialize_grid(int x, int y, int mod){
    width = x;
    height = y;
    game_grid= (Tile**) malloc(x * sizeof(Tile*));
    for (int h = 0; h < x; h++) {
        game_grid[h] = (Tile*) malloc(y*sizeof(Tile));
        for( int j = 0;j<y;j++){
            Tile t;
            game_grid[h][j] = t;
            if((rand() % mod)==0){
                Point p;
                p.type = 0;
                p.x=h;
                p.y=j;
                add_entity(p);
            }
        }
    }
    return game_grid;
}
