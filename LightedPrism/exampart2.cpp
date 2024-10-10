//--------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Exam #1 Part II
// Due Date --- October 2, 2024
//
// This program draws a three dimensional octagonal bipyramid. No two adjacent 
// faces have the same color. David Eck's camera API is included to enable the 
// user to rotate the figure with the mouse.
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

#include <vector>
#include <cmath>
#include "camera.h"  



std::vector<float> drawNGon(int n, float radius, float z) {
    std::vector<float> vertices;

    // Calculate the vertices of the n-gon in 3D
    for (int i = 0; i < n; ++i) {
        float angle = 2.0f * M_PI * i / n; // Calculate the angle
        float x = radius * cos(angle);      // X coordinate
        float y = radius * sin(angle);      // Y coordinate
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);               // Z coordinate
    }

    
    return vertices;
}

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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
    glMatrixMode(GL_MODELVIEW);
	
    cameraSetLimits(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
    cameraApply();       

    std::vector<float> vertices = drawNGon(50, 0.5, 0);

    int n = 50;

    float cube_color[] = { 0.7f, 0.0f, 0.7f, 1.0f };   // Go Bisons!
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    // Draw triangles
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < n; ++i) {
        // Center point at z=0 (or any desired z)
        glNormal3i(0,0,1);
        glVertex3f(0.0f, 0.0f, 0.0f);

        // Current vertex
        glVertex3f(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);

        // Next vertex (wrap around)
        int next = (i + 1) % n; // Wrap around to create the last triangle
        glVertex3f(vertices[next * 3], vertices[next * 3 + 1], vertices[next * 3 + 2]);
    }
    glEnd();

    

    glFlush();  // Render now
}

//------------------------------------------------------------------------------------
// init()
// 
// Various initializations. 
//------------------------------------------------------------------------------------
void init()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);      // Turn on a light. Use default light attributes.
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals
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
	init(); 
    glutMainLoop();
    return 0;
}
