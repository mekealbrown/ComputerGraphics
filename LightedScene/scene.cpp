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

float rotationAngle = 0.0f;
int lastTime = 0;
GLUquadric* quadric = nullptr;
float lightX = -0.2f, lightY = 1.0f, lightZ = 0.5f;



void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    cameraSetLimits(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0); 
    cameraApply();       

    GLfloat light_position[] = {lightX, lightY, lightZ, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // sphere as "light source"
    glPushMatrix();
        glTranslatef(lightX, lightY, lightZ);
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 1.0f, 0.0f);
        gluSphere(quadric, 0.05, 32, 32);
        glEnable(GL_LIGHTING);
    glPopMatrix();
    
    //table top
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f);
        drawPrism(4, 1.0f, 0.05f, BROWN);
    glPopMatrix();

    //leg 1
    glPushMatrix();
        glTranslatef(-0.8f, -0.5f, 0.0f);
        glRotatef(15.0f, 0.0f, 0.0f, -1.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();

    //leg 2
    glPushMatrix();
        glTranslatef(0.8f, -0.5f, 0.0f);
        glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();

    //leg 3
    glPushMatrix();
        glTranslatef(0.0f, -0.5f, 0.8f);
        glRotatef(15.0f, -1.0f, 0.0f, 0.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();

    //leg 4
    glPushMatrix();
        glTranslatef(0.0f, -0.5f, -0.8f);
        glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
        drawPrism(100, 0.04f, 1.0f, BROWN);
    glPopMatrix();
    
    //octagonal bipyramid :)
    glPushMatrix();
        glRotatef(rotationAngle, 0, 1, 0);
        glTranslatef(0.0f, 0.5f, 0.0f);
        drawPyramid(8, 0.3f, 0.3f, PURPLE);

        drawPyramid(8, 0.3f, -0.3f, PURPLE);
    glPopMatrix();


    glFlush();
}

void update(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    rotationAngle -= 30.0f * deltaTime;
    if (rotationAngle < 360.0f) {
        rotationAngle += 360.0f;
    }
    lastTime = currentTime;

    lightX = 1.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.001f);
    lightZ = 1.0f * cos(glutGet(GLUT_ELAPSED_TIME) * 0.001f);

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHT1);
    GLfloat light1_position[] = { 0.0f, 0.0f, 10.0f, 0.0f }; // w = 0 for directional
    GLfloat light1_diffuse[] = { 1.0f, 1.0f ,1.0f, 1.0f};     // Red light
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //gold..except it really just looks yellow
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lighted Scene");

    glutReshapeFunc(reshape);
    
    lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(0, update, 0);

    glutDisplayFunc(display);
    init(); 
    glutMainLoop();
    return 0;
}