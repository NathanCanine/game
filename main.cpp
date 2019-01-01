#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <time.h>       /* time */
#include <cstdlib>
#include "steppers.h"
#include "renderer.h"

void displayMe(bool **grid,int x,int y){
    std::cout<<"rendering once!";
    glClear(GL_COLOR_BUFFER_BIT);
    //glEnable(GL_TEXTURE_2D);
    for(int a =0; a < x; a++){
        for(int b = 0; b < y; b++){
            if(!grid[a][b]){
                continue;
            }
            glBegin(GL_POLYGON);
            float left = (2.0*a/x)-1.0;
            float right = (2.0*(a+1)/x)-1.0;
            float top = (2.0*b/y)-1.0;
            float bottom = (2.0*(b+1)/y)-1.0;
            glVertex2d(left,top);
            glVertex2d(right,top);
            glVertex2d(right,bottom);
            glVertex2d(left,bottom);
            glEnd();
            glPopMatrix();
            glPushMatrix();
        }
    }
    liveOrDie(grid,x,y);
    //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
    glFlush();
    glutPostRedisplay();
}

template <class F>
auto cify_no_args(F&& f) {
  static F fn = std::forward<F>(f);
  return [] {
    return fn();
  };
}

int main(int argc, char** argv){
    srand(time(NULL));
    int x = 480;
    int y = 270;
    bool** grid = initialize_grid(x,y);
    initialize(argc,argv);
    glutDisplayFunc( cify_no_args([&](){
        displayMe(grid,x,y);
    }));
    glutMainLoop();
}
