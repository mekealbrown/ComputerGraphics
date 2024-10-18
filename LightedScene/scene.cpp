#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

#include "camera.h"
#include "cylinder.hpp"

const float CUBE_COLOR[] = { 0.7f, 0.0f, 0.7f, 1.0f };



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    cameraSetLimits(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
    cameraApply();       

    float background[] = {1.0f, 0.8f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CUBE_COLOR);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CUBE_COLOR);
    glMaterialfv(GL_FRONT, GL_AMBIENT, background);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    glColor3fv(CUBE_COLOR);
    

    drawPrism(4, 0.1f, 0.3f, CUBE_COLOR);

    glPushMatrix();
      glTranslatef(0.0f, 0.0f, -0.4f);
      drawPrism(1000, 0.1f, 0.3f, CUBE_COLOR);
    glPopMatrix();
    
    glFlush();
}

void init() {
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glClearColor(1.0f, 0.8f, 0.0f, 1.0f); //gold..except it really just looks yellow
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lighted Scene");
    glutDisplayFunc(display);
    init(); 
    glutMainLoop();
    return 0;
}