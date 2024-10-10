//--------------------------------------------------------------------------
// Developer -- Bryan Crawley
// Course ----- CS3233
// Project ---- Class demo
//
// Draw a multicolored cube and give it a slight rotation. Enable the user
// to spin it with the mouse using Eck's trackball API.
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

#include "camera.h"  // Eck's camera API. You also need to compile
                     // and link camera.cpp

//------------------------------------------------------------------------------------
// display()
//
// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
//------------------------------------------------------------------------------------

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //glMatrixMode(GL_PROJECTION);                    // Removed for Eck's camera API
    //glLoadIdentity();                               // Removed for Eck's camera API
    //glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f); // Removed for Eck's camera API
	
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // Replace the 3 lines above.
    cameraApply();                                    // Replace the 3 lines above.

    glRotatef(35.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
       // Front
       glColor3f(1.0f, 0.0f, 0.0f);   // Red
       glVertex3i(0, 1, 1);
       glVertex3i(0, 0, 1);
       glVertex3i(1, 0, 1);
       glVertex3i(1, 1, 1);
	glEnd();

    glBegin(GL_TRIANGLE_FAN);
       // Right
       glColor3f(0.0f, 0.0f, 1.0f);   // Blue
       glVertex3i(1, 1, 1);
       glVertex3i(1, 0, 1);
       glVertex3i(1, 0, 0);
       glVertex3i(1, 1, 0);
	glEnd();

    glBegin(GL_TRIANGLE_FAN);
       // Back
       glColor3f(1.0f, 0.35f, 0.0f);  // Orange
       glVertex3i(1, 1, 0);
       glVertex3i(1, 0, 0);
       glVertex3i(0, 0, 0);
       glVertex3i(0, 1, 0);
	glEnd();

    glBegin(GL_TRIANGLE_FAN);
       // Left
       glColor3f(0.0f, 0.6f, 0.0f);   // Green
       glVertex3i(0, 1, 0);
       glVertex3i(0, 0, 0);
       glVertex3i(0, 0, 1);
       glVertex3i(0, 1, 1);
	glEnd();

    glBegin(GL_TRIANGLE_FAN);
       // Top
       glColor3f(1.0f, 1.0f, 1.0f);   // White
       glVertex3i(0, 1, 0);
       glVertex3i(0, 1, 1);
       glVertex3i(1, 1, 1);
       glVertex3i(1, 1, 0);
	glEnd();

    glBegin(GL_TRIANGLE_FAN);
       // Bottom
       glColor3f(1.0f, 1.0f, 0.0f);   // Yellow
       glVertex3i(0, 0, 0);
       glVertex3i(0, 0, 1);
       glVertex3i(1, 0, 1);
       glVertex3i(1, 0, 0);
	glEnd();

    glFlush();  // Render now
}

//------------------------------------------------------------------------------------
// init()
// 
// Various initializations. For now, these pertain to using Eck's camera API.
// We may add others later.
//------------------------------------------------------------------------------------
void init()
{
    glutMouseFunc(trackballMouseFunction);    // Register Eck's mouse-click function.
    glutMotionFunc(trackballMotionFunction);  // Register Eck's mouse-motion function.
    return;
}

//------------------------------------------------------------------------------------
// main()
//
// Main function. GLUT initalizations and the main event loop.
//------------------------------------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Unit Cube With Rotation");
    glutDisplayFunc(display);
	init();  // Just be sure you do this before the main loop.
    glutMainLoop();
    return 0;
}
