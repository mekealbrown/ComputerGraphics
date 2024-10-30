//-------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #5: Awesome Sauce
// Due Date --- November 1, 2024
//
// This program draws an unopened box of Tabasco sauce and, of course, a Utah
// teapot on a table.
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
    
  cameraSetLimits(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
  cameraApply();       

    //table top
  glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    drawPrism(4, 1.0f, 0.05f, GOLD);
  glPopMatrix();

    //leg 1
  glPushMatrix();
    glTranslatef(-0.8f, -0.5f, 0.0f);
    glRotatef(15.0f, 0.0f, 0.0f, -1.0f);
    drawPrism(100, 0.04f, 1.0f, GOLD);
  glPopMatrix();

    //leg 2
  glPushMatrix();
    glTranslatef(0.8f, -0.5f, 0.0f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    drawPrism(100, 0.04f, 1.0f, GOLD);
  glPopMatrix();

    //leg 3
  glPushMatrix();
    glTranslatef(0.0f, -0.5f, 0.8f);
    glRotatef(15.0f, -1.0f, 0.0f, 0.0f);
    drawPrism(100, 0.04f, 1.0f, GOLD);
  glPopMatrix();

    //leg 4
  glPushMatrix();
    glTranslatef(0.0f, -0.5f, -0.8f);
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
    drawPrism(100, 0.04f, 1.0f, GOLD);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.2f, 0.02f, 0.0f);
    drawTabascoBox(0.1f);
  glPopMatrix();

  glPushMatrix();
    float specularColor[] = {1.0f, 1.0f, 0.0f, 1.0f}; // trying to get that shine
    float ambientColor[] = {0.25f, 0.20f, 0.0f, 1.0f};
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, BLACK);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0f);
    glTranslatef(-0.3f, 0.1f, 0.2f);
    glutSolidTeapot(0.1);
  glPopMatrix();

  glFlush();
}


void init() {
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);

    int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* data = stbi_load("TabascoSauceTexture.jpg", &imgWidth, &imgHeight, &bytesPerPixel, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);

    glClearColor(0.7f, 0.0f, 0.7f, 1.0f); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Awesome Sauce");
    glutDisplayFunc(display);
    init(); 
    glutMainLoop();
    return 0;
}