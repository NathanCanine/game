#include <cstdlib>
#include "steppers.h"
#include <iostream>

int die_length = 0;
int *die_ranges= {};
int *birth_ranges = {};
int birth_length = 0;

void set_die_ranges(int *die_ranges_arg, int length){
    die_ranges = die_ranges_arg;
    die_length = length;
}

void set_birth_ranges(int *birth_ranges_arg, int length){
    birth_ranges = birth_ranges_arg;
    birth_length = length;
}

bool should_die(int life){
    for (int i=0;i<die_length;i++){
        if(die_ranges[2*i]<=life && life <= die_ranges[(2*i) + 1]){
            return true;
        }
    }
    return false;
}

bool should_birth(int life){
    for (int i=0;i<birth_length;i++){
        if(birth_ranges[2*i]<=life && life <= birth_ranges[(2*i) + 1]){
            return true;
        }
    }
    return false;
}

//Calculates Life or Death
void step(Tile **grid,int x, int y){
    for(int a = 0; a < x; a++){
        for(int b = 0; b < y; b++){
            int life = 0;
            for(int c = -1; c < 2; c++){
                for(int d = -1; d < 2; d++){
                    int apc = a+c;
                    int bpd = b+d;
                    if(apc == -1 || apc == x || bpd == -1 || bpd == y || (apc == a && bpd == b)){
                    } else if (grid[apc][bpd].grassy){
                        ++life;
                    }
                }
            }
            if(!grid[a][b].grassy && should_birth(life)){
                grid[a][b].next_grassy = true;
            } else if(should_die(life)) {
                grid[a][b].next_grassy = false;
            }
        }
    }

    for(int a = 0; a < x; a++){
        for(int b = 0; b < y; b++){
            grid[a][b].grassy = grid[a][b].next_grassy;
        }
    }
}

//Calculates Life or Death
void liveOrDieCool(Tile **grid,int x, int y){
    for(int a = 0; a < x; a++){
        for(int b = 0; b < y; b++){
            int life = 0;
            for(int c = -1; c < 2; c++){
                for(int d = -1; d < 2; d++){
                    int apc = a+c;
                    int bpd = b+d;
                    if(apc == -1 || apc == x || bpd == -1 || bpd == y){

                    } else if (grid[apc][bpd].grassy){
                        ++life;
                    }
                }
            }
            if(life < 2) {
                grid[a][b].grassy = false;
            } else if(life == 3){
                grid[a][b].grassy = true;
            } else if(life > 3){
                grid[a][b].grassy = false;
            }
        }
    }
}

Tile** initialize_grid(int x, int y, int mod){
    Tile** grid= (Tile**) malloc(x * sizeof(Tile*));
    for (int h = 0; h < x; h++) {
        grid[h] = (Tile*) malloc(y*sizeof(Tile));
        for( int j = 0;j<y;j++){
            Tile t((rand() % mod)==1);
            grid[h][j] = t;
        }
    }
    return grid;
}
