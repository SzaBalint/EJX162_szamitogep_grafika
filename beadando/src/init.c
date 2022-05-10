#include <GL/glut.h>

#include "init.h"

void initialize()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    
    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

    gluPerspective(50.0, (16.0 / 9.0), 0.01, 1000.0);
}
