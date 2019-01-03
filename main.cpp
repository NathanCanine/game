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
#include "SOIL.h"

void displayMe(bool **grid,int x,int y){
    glClear(GL_COLOR_BUFFER_BIT);


    GLuint tex = SOIL_load_OGL_texture
	(
		"grass.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    GLuint tex2 = SOIL_load_OGL_texture
	(
		"dirt.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    //clear and draw quad with texture (could be in display callback)
    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    for(int a =0; a < x; a++){
        for(int b = 0; b < y; b++){
            if(grid[a][b]){
                glBindTexture(GL_TEXTURE_2D, tex);
            } else {
                glBindTexture(GL_TEXTURE_2D,tex2);
            }
            glBegin(GL_POLYGON);
            float left = (2.0*a/x)-1.0;
            float right = (2.0*(a+1)/x)-1.0;
            float top = (2.0*b/y)-1.0;
            float bottom = (2.0*(b+1)/y)-1.0;
            glVertex2d(left,top);  glTexCoord2f( 0.0 , 0.0 );
            glVertex2d(right,top); glTexCoord2f( 1.0 , 0.0 );
            glVertex2d(right,bottom); glTexCoord2f( 1.0 , 1.0 );
            glVertex2d(left,bottom); glTexCoord2f( 0.0 , 1.0 );
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
    int x = 64;
    int y = 64;
    bool** grid = initialize_grid(x,y);
    initialize_renderer(argc,argv,x,y,cify_no_args([&](){
        displayMe(grid,x,y);
    }));
}
