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

#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <cmath>
#include <iostream>

#include "stb_image.h"
#include "camera.h"
#include "shapes.h"

//helpful globals
int lastTime = 0;


//--------------------------------------------------------------------
// display()
//
// This function calls the functions responsible for drawing the 
// objects to create the scene, along with setting up some state
//--------------------------------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    cameraSetLimits(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0); 
    cameraApply();       

    drawDrCrawleyBoard(360, 1.0f, 0.05f, WHITE);

    drawDart(5.0f);

    glFlush();
}


//--------------------------------------------------------------------
// update()
//
// This function updates position parameters for animated objects
//--------------------------------------------------------------------
void update(int value) {
    //int currentTime = glutGet(GLUT_ELAPSED_TIME);
    //float deltaTime = (currentTime - lastTime) / 1000.0f;

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

    int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* data = stbi_load("MyFace.jpg", &imgWidth, &imgHeight, &bytesPerPixel, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glEnable(GL_NORMALIZE);
    

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