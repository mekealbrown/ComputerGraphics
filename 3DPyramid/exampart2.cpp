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
#include "camera.h"  


//--------------------------------------------------------------------------
// rotateVector()
//
// This functions shuffles all elements of a 2D vector down and wraps the 
// last element back to the front. 
//--------------------------------------------------------------------------
void rotateVector(std::vector<std::vector<float>>& vec) {
    std::vector<float> lastElement = vec.back(); // Store last
    for (size_t i = vec.size() - 1; i > 0; --i) {
        vec[i] = vec[i - 1]; // Shift down
    }
    vec[0] = lastElement; // Wrap last to front
}


//--------------------------------------------------------------------------
// drawPyramid()
//
// This function takes a vertex representing the apex of a pyramid and draws
// and octagonal pyramid with pre-calculated points(faster). For bipyramidal 
// drawing, flip the y in the passed in vertex.
//
//
// Points calculated with the following: 
//      while i <= 8
//      angle = 2.0f * M_PI * i / 8
//      x = 0.5f * cos(angle)
//      y = 0
//      z = 0.5f * sin(angle)
//--------------------------------------------------------------------------
void drawPyramid(const float apex[3], const std::vector<std::vector<float>>& colors)
{
    const float points[][18] = {
        {0.5 ,0, 0},
        {0.353553 ,0, 0.353553},

        {-2.18557e-08 ,0, 0.5},
        {-0.353553 ,0, 0.353553},

        {-0.5 ,0, -4.37114e-08},
        {-0.353553 ,0, -0.353553},

        {5.96244e-09 ,0, -0.5},
        {0.353553 ,0, -0.353553},

        {0.5 ,0, 8.74228e-08},
        {0.5 ,0, 0},

        {0.353553 ,0, 0.353553},
        {-2.18557e-08 ,0, 0.5},

        {-0.353553 ,0, 0.353553},
        {-0.5 ,0, -4.37114e-08},

        {-0.353553 ,0, -0.353553},
        {5.96244e-09 ,0, -0.5},

        {0.353553 ,0, -0.353553},
        {0.5 ,0, 8.74228e-08}
    };

    glBegin(GL_TRIANGLES);
        for(int i = 0; i < 9; ++i) {
            glColor4f(colors[i][0], colors[i][1], colors[i][2], 0.6f);

            glVertex3fv(apex);  //apex vertex
            glVertex3fv(points[i]);
            glVertex3fv(points[i+1]);
        }
    glEnd();
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
    cameraSetLimits(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
    cameraApply();       

    std::vector<std::vector<float>> colors = {
        {0.95f, 0.61f, 0.18f},   
        {0.18f, 0.62f, 0.80f},   
        {0.87f, 0.28f, 0.46f},  
        {0.38f, 0.80f, 0.69f},  
        {0.62f, 0.30f, 0.87f},  
        {0.22f, 0.75f, 0.42f},   
        {0.95f, 0.36f, 0.25f},  
        {0.38f, 0.43f, 0.87f},   
        {0.80f, 0.78f, 0.15f} 
    };                             

    float apex[3] = {0.0f, 0.7f, 0.0f};
    drawPyramid(apex, colors);

    apex[1] = -0.7f;
    rotateVector(colors); //no adjacent faces are the same color
    drawPyramid(apex, colors);

    glFlush();  // Render now
}

//------------------------------------------------------------------------------------
// init()
// 
// Various initializations. 
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
	init(); 
    glutMainLoop();
    return 0;
}
