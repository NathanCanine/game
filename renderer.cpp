#include "renderer.h"
#include <GL/glut.h>

void initialize_renderer(int argc, char** argv, int x, int y, void (*callback)()){
    glutInit(&argc, argv);
    glutInitWindowSize(x, y);
    glutCreateWindow("OpenGL"); // creating the window
    glutFullScreen();
    glutDisplayFunc(callback);
    glutMainLoop();
}
