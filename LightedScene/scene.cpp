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
#include "shapes.hpp"


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); 
    cameraApply();       
    
    //table top
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -0.4f);
        drawPrism(4, 1.0f, 0.05f, BROWN);
    glPopMatrix();

    //leg 1
    glPushMatrix();
        glTranslatef(-0.8f, -0.5f, -0.4f);
        glRotatef(15.0f, 0.0f, 0.0f, -1.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();

    //leg 2
    glPushMatrix();
        glTranslatef(0.8f, -0.5f, -0.4f);
        glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();

    //leg 3
    glPushMatrix();
        glTranslatef(0.0f, -0.5f, 0.4f);
        glRotatef(15.0f, -1.0f, 0.0f, 0.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();

    //leg 4
    glPushMatrix();
        glTranslatef(0.0f, -0.5f, -1.2f);
        glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f, 0.5f, -0.4f);
        drawOctagonalBipyramid(0.3f, 0.3f);
    glPopMatrix();

    glFlush();
}

void init() {
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glClearColor(0.02f, 0.02f, 0.02f, 1.0f); //gold..except it really just looks yellow
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