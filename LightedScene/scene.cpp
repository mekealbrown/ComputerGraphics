//-------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #4: Lighted Scene
// Due Date --- October 23, 2024
//
// This program draws a lighted scene containing a table, an octagonal bipyramid,
// an rotating light source, a Utah teapot, and some text.
//-------------------------------------------------------------------------------
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

#include "camera.h"
#include "shapes.hpp"

//helpful globals
float rotationAngle = 0.0f;
int lastTime = 0;
GLUquadric* quadric = nullptr;
float lightX = -0.2f, lightY = 1.0f, lightZ = 0.5f;

//--------------------------------------------------------------------
// display()
//
// This function calls the functions responsible for drawing the 
// objects to create the scene, along with setting up some state
//--------------------------------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    cameraSetLimits(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0); 
    cameraApply();       

    drawText(-1.0f, 2.0f, 0.0f, "So how are we all doing today");

    float light_position[] = {lightX, lightY, lightZ, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // sphere as "light source"
    glPushMatrix();
        glTranslatef(lightX, lightY, lightZ);
        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 1.0f, 0.0f);
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

    glPushMatrix();
        float diffuseColor[] = {0.75f, 0.61f, 0.25f, 1.0f};
        float specularColor[] = {1.0f, 1.0f, 0.0f, 1.0f}; // trying to get that shine
        float ambientColor[] = {0.25f, 0.20f, 0.0f, 1.0f};

        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
        glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
        glTranslatef(-0.3f, 0.1f, 0.2f);
        glutSolidTeapot(0.1);
    glPopMatrix();

    glFlush();
}


//--------------------------------------------------------------------
// update()
//
// This function updates position parameters for animated objects
//--------------------------------------------------------------------
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

//--------------------------------------------------------------------
// reshape()
//
// This function sets up how the scene is viewed and scaled when 
// the window is resized
//--------------------------------------------------------------------
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
    GLfloat light1_position[] = { 0.0f, 0.0f, 10.0f, 0.0f }; 
    GLfloat light1_diffuse[] = { 1.0f, 1.0f ,1.0f, 1.0f}; 
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    glEnable(GL_NORMALIZE);
    
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
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