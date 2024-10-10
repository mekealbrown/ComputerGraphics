//--------------------------------------------------------------------------
// Developer -- Bryan Crawley, et al.
// Course ----- CS3233
// Project ---- Normal vector demo
// Due date --- N/A
// 
// Demonstrate the effects of various normal vectors on a flat rectangle.
// We're using the trackball feature of David Eck's camera API.
//--------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include "camera.h"

//--------------------------------------------------------------------------
// display()
//--------------------------------------------------------------------------

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

	 cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	 cameraApply();

    // Use these points for the vertices of the rectangle.
    int point[][3] = {
        {1,0,0}, {1,1,0}, {0,1,1}, {0,0,1}
    };

    float axis_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float rectangle_color[] = { 0.5f, 0.0f, 0.5f, 1.0f };   // Go Bisons!

	 // Set the material for drawing the axes.
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, axis_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, axis_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, axis_color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0F);

	 // Draw lines on the axes so we can see them.
	 glBegin(GL_LINES);
	    glVertex3i(-2,  0,  0);  // x axis
		 glVertex3i( 2,  0,  0);
		 glVertex3i( 0, -2,  0);  // y axis
		 glVertex3i( 0,  2,  0);
		 glVertex3i( 0,  0, -2);  // z axis
		 glVertex3i( 0,  0,  2);
	 glEnd();

	 // Set the material for drawing the rectangle.
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rectangle_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, rectangle_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, rectangle_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0F);

	 // Draw the rectangle.
    glBegin(GL_TRIANGLE_FAN);
       glNormal3f(1.0, 0.0, 0.0);
       glVertex3iv(point[0]);
       glVertex3iv(point[1]);
       glNormal3f(0.0, 0.0, 1.0);
       glVertex3iv(point[2]);
       glVertex3iv(point[3]);
    glEnd();

    glFlush();
}

//--------------------------------------------------------------------------
// init() -- Various initializations
//--------------------------------------------------------------------------

void init()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
	 glutMouseFunc(trackballMouseFunction);
	 glutMotionFunc(trackballMotionFunction);
    return;
}

//--------------------------------------------------------------------------
// main
//--------------------------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1400, 800);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Normal vector demonstration");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
