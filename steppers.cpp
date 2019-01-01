#include <cstdlib>
#include "steppers.h"

//This copy's the grid for comparision purposes.
void CopyGrid (bool **grid,bool **grid2, int x, int y){
    for(int a = 0; a < x; a++){
        for(int b = 0; b < y; b++){
            grid2[a][b] = grid[a][b];
        }
    }
}

//Calculates Life or Death
void liveOrDie(bool **grid,int x, int y){
    bool** grid2= (bool**) malloc(x * sizeof(bool*));
    for (int h = 0; h < x; h++) {
        grid2[h] = (bool*) malloc(y*sizeof(bool));
    }
    CopyGrid(grid, grid2,x,y);
    for(int a = 0; a < x; a++){
        for(int b = 0; b < y; b++){
            int life = 0;
            for(int c = -1; c < 2; c++){
                for(int d = -1; d < 2; d++){
                    int apc = a+c;
                    int bpd = b+d;
                    if(apc == -1 || apc == x || bpd == -1 || bpd == y || (apc == a && bpd == b)){
                    } else if (grid2[apc][bpd]){
                        ++life;
                    }
                }
            }
            if(!grid2[a][b] && life == 3){
                grid[a][b] = true;
            } else if(life < 2) {
                grid[a][b] = false;
            } else if(life > 3){
                grid[a][b] = false;
            }
        }
    }
    for(int i =0;i<x;i++){
        free(grid2[i]);
    }
    free(grid2);
}

//Calculates Life or Death
void liveOrDieCool(bool **grid,int x, int y){
    bool** grid2= (bool**) malloc(x * sizeof(bool*));
    for (int h = 0; h < x; h++) {
        grid2[h] = (bool*) malloc(y*sizeof(bool));
    }
    CopyGrid(grid, grid2,x,y);
    for(int a = 0; a < x; a++){
        for(int b = 0; b < y; b++){
            int life = 0;
            for(int c = -1; c < 2; c++){
                for(int d = -1; d < 2; d++){
                    int apc = a+c;
                    int bpd = b+d;
                    if(apc == -1 || apc == x || bpd == -1 || bpd == y){

                    } else if (grid[apc][bpd]){
                        ++life;
                    }
                }
            }
            if(life < 2) {
                grid[a][b] = false;
            } else if(life == 3){
                grid[a][b] = true;
            } else if(life > 3){
                grid[a][b] = false;
            }
        }
    }
}

bool** initialize_grid(int x, int y){
    bool** grid= (bool**) malloc(x * sizeof(bool*));
    for (int h = 0; h < x; h++) {
        grid[h] = (bool*) malloc(y*sizeof(bool));
        for( int j = 0;j<y;j++){
            grid[h][j] = ((rand() % 2)==1);
        }
    }
    return grid;
}
