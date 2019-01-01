#include "renderer.h"
#include <GL/glut.h>

void initialize(int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // enabling double buffering and RGBA
    glutInitWindowSize(600, 600);
    glutCreateWindow("OpenGL"); // creating the window
    glutFullScreen(); 
}
