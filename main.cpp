#include <iostream>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include <ctime>
#include <time.h>       /* time */
#include <cstdlib>
#include "steppers.h"
#include "renderer.h"
#include "SOIL.h"
#include "entity.h"
#include <map>


uint32_t mouse_status = 0;

void onMouseButton(int button, int state, int x, int y)
{
    std::cout<<"GELLLER! CLICKY WORLD!\n";
    glutPostRedisplay();
}


void displayMe(Tile **grid,int x,int y){
    glClear(GL_COLOR_BUFFER_BIT);
    GLuint tex = SOIL_load_OGL_texture
	(
		"grass.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
    GLuint tex2 = SOIL_load_OGL_texture
	(
		"dirt.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
    GLuint tex3 = SOIL_load_OGL_texture
	(
		"grass_less.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    //clear and draw quad with texture (could be in display callback)
    glClear(GL_COLOR_BUFFER_BIT);
    //glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    for(int a =0; a < x; a++){
        for(int b = 0; b < y; b++){
            if(grid[a][b].population>0){
                if(grid[a][b].get_entities()[0]->entity_type==0){
                    glBindTexture(GL_TEXTURE_2D, tex);
                } else {
                    continue;
                    glBindTexture(GL_TEXTURE_2D, tex3);
                }
            } else {
                continue;
                glBindTexture(GL_TEXTURE_2D, tex2);
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
    //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1));
    glFlush();
    step();
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
    srand(0);//time(NULL));
    int x = 120;
    int y = 70;
    Tile **game_grid = initialize_grid(x,y,5);
    initialize_renderer(argc,argv,x,y,cify_no_args([&](){
        displayMe(game_grid,x,y);
    }));
}
