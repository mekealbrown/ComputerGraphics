//--------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #6: Take that!
// Due Date --- November 13, 2024
//
// This program draws a cylindrical cylinder with a texture mapping of Dr. Crawley
// and an animated dart that is on an eerily accurate trajectory right toward his 
// face!
//--------------------------------------------------------------------------------
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
int last_time = 0;
bool has_impacted = false;
float pos_x = 0.0f; 
float pos_y = 1.5f;
float pos_z = 0.0f;

//--------------------------------------------------------------------
// display()
//
// This function calls the functions responsible for drawing the 
// objects to create the scene, along with setting up some state
//--------------------------------------------------------------------
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  cameraSetLimits(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
  cameraApply();
    
  glPushMatrix();
  glRotatef(70, 1.0f, 0.0f, 0.0f);
  glRotatef(35, 0.0f, 0.0f, 1.0f);
    
	drawDrCrawleyBoard(360, 1.0f, 0.05f, WHITE);
    
  // Draw dart
  glPushMatrix();
    glTranslatef(pos_x, pos_y, pos_z);
    drawDart(5.0f);
  glPopMatrix();
    
	if(has_impacted){
		drawText(pos_x + 2.0f, pos_y + 2.0f, pos_z, "Well, hello there.");
	}
    
  glPopMatrix();
  glFlush();
}
//--------------------------------------------------------------------
// update()
//
// This function updates position parameters for animated objects
//--------------------------------------------------------------------
void update(int value) {
	if(pos_y >= 0.18f){
		pos_y -= 0.001f;
	}
	else{
		has_impacted = true;
	}

  glutPostRedisplay();
  glutTimerFunc(1, update, 0);
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
  glutCreateWindow("Take that!");

  glutReshapeFunc(reshape);

	last_time = glutGet(GLUT_ELAPSED_TIME);
  glutTimerFunc(0, update, 0);

  glutDisplayFunc(display);
  init(); 
  glutMainLoop();
  return 0;
}