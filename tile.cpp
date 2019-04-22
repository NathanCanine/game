#include "entity.h"
#include "tile.h"
#include <cstdlib>
#include <iostream>

Tile::Tile(){
    entities = (Entity**)malloc(16 * sizeof(Entity*));
    population = 0;
    projecting = ( Entity**) malloc(16*sizeof(Entity*));
    num_projecting = 0;
}

Entity* Tile::add_entity(Point p){
	if(population>0){
		return nullptr;
	}
    Entity *e = (Entity*)malloc(sizeof(Entity));
    e->entity_type=p.type;
	entities[population++] = e;
	return e;
}

Entity* Tile::remove_entity(int id){
    for(int i=0;i<population;i++){
        if((*entities[i]).get_id() == id){
            Entity* ret = entities[i];
            if(population==1){
                population--;
                return ret;
            }
            entities[i] = entities[--population];
            return ret;
        }
    }
    return nullptr;
}

bool Tile::add_projecting(Entity *e){
	if(num_projecting==16){
		return false;
	}
	projecting[num_projecting++] = e;
	return true;
}

Entity** Tile::get_projecting(){
	return projecting;
}


Entity** Tile::get_entities(){
	return entities;
}

void Tile::reset(){
    num_projecting = 0;
    completed=false;
}
