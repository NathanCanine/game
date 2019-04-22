#include "entity.h"
#include <cstdlib>
#include <iostream>

Entity::Entity(){
  int interactions = 0;
  int id = 0;
  int entity_type=-1;
}

Projection Entity::project(){
    struct Projection projection;
    if(entity_type==1){
        projection.length==0;
    } else {
        int k=0;
        for(int i=-1;i<2;i++){
            for(int j=-1;j<2;j++){
                if(!(i==0&&j==0)){
                    projection.points[k++] = {i,j};
                }
            }
        }
        projection.length=8;
    }
    return projection;
}

void Entity::interact(){
    interactions++;
}

bool Entity::resolve(){
    if(entity_type==1&&interactions==3){
        entity_type=0;
        return false;
    } else if(entity_type==0&&(interactions>3 || interactions<2)){
        entity_type=1;
        return false;
    }
    return false;
}

void Entity::reset(){
    interactions = 0;
}

void Entity::act(Entity** locals, int local_pop, Entity** projectors, int projecting){
    for(int i=0;i<projecting;i++){
       // projectors[i]->interact();
    }
    for(int i=0;i<local_pop;i++){
        locals[i]->interact();
    }
}


int Entity::place(Entity** locals, int local_pop, Entity** projectors, int projecting){
    if (projecting==3&&local_pop==0){
        return 0;
    }
    return -1;
}

int Entity::get_id(){
    return id;
}

void Entity::set_id(int i){
    id = i;
}

void plan(){
}
