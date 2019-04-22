#include "renderer.h"
#include <GL/glut.h>
#include <iostream>

void mouseClicks(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //onMouse = 1;
    }
    std::cout<<"HELLER WORLD!!!\n";
}

void initialize_renderer(int argc, char** argv, int x, int y, void (*callback)()){
    glutInit(&argc, argv);
    glutInitWindowSize(x, y);
    glutCreateWindow("OpenGL"); // creating the window
    glutFullScreen();
    glutPostRedisplay();
    glutMouseFunc(mouseClicks);
    glutDisplayFunc(callback);
    glutMainLoop();
}
