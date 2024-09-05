//------------------------------------------------------------------------------------
// Developer---Mekeal Brown
// Course------CS3233-01
// Project-----Homework #1
// Due---------September 11, 2024
// 
// This program draws a house, a tree, a pretty sun, some clouds, and some purple water
//------------------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif


#include <iostream>
#include <thread>
#include <math.h>

// Point struct to store calculated points
struct Point {float x, y;};

//------------------------------------------------------------------------------------
// drawTree()
//
// Handles drawing trees and their shadows
//------------------------------------------------------------------------------------
void drawTree(float x, float y, float size) {
    Point p1 = {x - size*0.05f, y};
    Point p2 = {x - size*0.05f, y + size*0.6f};
    Point p3 = {x + size*0.05f, y};
    Point p4 = {x + size*0.05f, y + size*0.6f};

    // Trunk
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.25f, 0.05f, 0.0f);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, p4.y);
    glEnd();

    // Tree shadow
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0039f, 0.1019f, 0.0039f);  
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, y - size*0.6f);
        glVertex2f(p3.x, p3.y);
        glVertex2f(p4.x, y - size*0.6f);
    glEnd();

    // Leaves
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.1f, 0.5f, 0.1f);
        glVertex2f(x, y + size);  // Top of the tree
        for (int i = 0; i <= 180; i += 30) {
            float angle = i * 3.14159f / 180.0f;
            float leafX = x + size * 0.3f * cos(angle);
            float leafY = y + size * 0.4f + size * 0.3f * sin(angle);
            glVertex2f(leafX, leafY);
        }
    glEnd();

    // Lighter green patches for depth
    glBegin(GL_TRIANGLES);
        glColor3f(0.2f, 0.6f, 0.2f);
        glVertex2f(x, y + size);
        glVertex2f(x - size*0.15f, y + size*0.6f);
        glVertex2f(x + size*0.15f, y + size*0.6f);
    glEnd();
}

//------------------------------------------------------------------------------------
// drawHouse()
//
// Handles drawing the house and its elements and shadow
//------------------------------------------------------------------------------------
void drawHouse(float x, float y, float size) {
    Point p1 = {x - size/2, y};
    Point p2 = {x + size/2, y};
    Point p3 = {x + size/2, y + size*0.8f};
    Point p4 = {x - size/2, y + size*0.8f};
    // Main structure
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5f, 0.4f, 0.3f);
        glVertex2f(p2.x, p2.y);  

        glColor3f(0.8f, 0.7f, 0.6f);  
        glVertex2f(p1.x, p1.y);

        glColor3f(0.5f, 0.4f, 0.3f);
        glVertex2f(p3.x, p3.y); //tr
        
        glColor3f(0.8f, 0.7f, 0.6f);
        glVertex2f(p4.x, p4.y); //tl
    glEnd();

    // Shadow
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.0039f, 0.1019f, 0.0039f);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x + 1.1f, -1.5);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p4.x + 0.6f, -2.0f);
    glEnd();

    // Roof
    glBegin(GL_TRIANGLES);
        glColor3f(0.5f, 0.2f, 0.2f);
        glVertex2f(x - size*0.6f, y + size*0.8f);
        glColor3f(0.2f, 0.01f, 0.01f);
        glVertex2f(x + size*0.6f, y + size*0.8f);
        glVertex2f(x, y + size*1.2f);
    glEnd();

    // Window
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.15f, 0.15f, 0.25f);
        glVertex2f(x - size*0.12f - 0.15f, y + size*0.5f);
        glVertex2f(x + size*0.12f - 0.15f, y + size*0.5f);
        glVertex2f(x - size*0.12f - 0.15f, y + size*0.7f);
        glVertex2f(x + size*0.12f - 0.15f, y + size*0.7f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(x - size*0.12f + 0.15f, y + size*0.5f);
        glVertex2f(x + size*0.12f + 0.15f, y + size*0.5f);
        glVertex2f(x - size*0.12f + 0.15f, y + size*0.7f);
        glVertex2f(x + size*0.12f + 0.15f, y + size*0.7f);
    glEnd();
    

    // Door
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.2f, 0.01f, 0.05f);
        glVertex2f(x - size*0.12f, y + size*0.5f - 0.3f);
        glVertex2f(x + size*0.12f, y + size*0.5f - 0.3f);
        glVertex2f(x - size*0.12f, y + size*0.9f - 0.3f);
        glVertex2f(x + size*0.12f, y + size*0.9f - 0.3f);
    glEnd();

    
}

//------------------------------------------------------------------------------------
// drawLand()
//
// Handles drawing the land...and some water
//------------------------------------------------------------------------------------
void drawLand() {
    // Land
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0353f, 0.3686f, 0.0118f); 

        glVertex2f(1.0f, -1.0f);
        glVertex2f(-2.0f, -1.0f);
        glVertex2f(1.0f, -0.7f);

        glVertex2f(-0.6f, -0.7f);
        glVertex2f(1.0, -0.7f);

        glVertex2f(-0.6f, -0.7f);
        glVertex2f(-2.0f, -1.0f);
    glEnd();

    // Water..yes, purple water GO BISONS
    glBegin(GL_TRIANGLES);
        glColor3f(0.325f, 0.165f, 0.522f);

        glVertex2f(-0.6f, -0.7f);
        glVertex2f(-2.0, -1.0f);
        glVertex2f(-2.0f, -0.7f);
    glEnd();
}

//------------------------------------------------------------------------------------
// drawCircle()
//
// Handles the drawing of a circle given starting pos, radius, and num of segments
//------------------------------------------------------------------------------------

void drawCircle(float cenX, float cenY, float rad, int n_segs) {
    float angleStep = 2.0f * 3.14159f / n_segs;  // Angle between each segment

    glBegin(GL_TRIANGLE_FAN);
        // Center vertex
        glVertex2f(cenX, cenY);
        for (int i = 0; i <= n_segs; ++i) {
            float angle = i * angleStep;
            float x = cenX + rad * cos(angle);
            float y = cenY + rad * sin(angle);
            glVertex2f(x, y);
        }
    glEnd();
}

//------------------------------------------------------------------------------------
// drawCloud()
//
// Draws several overlapping circles to form a cloud
//------------------------------------------------------------------------------------
void drawCloud(float x, float y, float size) {
    glColor3f(0.76f, 0.666f, 0.57f); 
    float radius = size * 0.5f;
    
    drawCircle(x, y, radius, 100); // Main circle
    drawCircle(x - radius * 0.6f, y + radius * 0.6f, radius * 0.8f, 100); 
    drawCircle(x + radius * 0.6f, y + radius * 0.6f, radius * 0.8f, 100);
    drawCircle(x - radius * 0.9f, y - radius * 0.4f, radius * 0.7f, 100);
    drawCircle(x + radius * 0.9f, y - radius * 0.4f, radius * 0.7f, 100);
}

//------------------------------------------------------------------------------------
// display()
//
// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
//------------------------------------------------------------------------------------
void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

    float alpha = 1.0f;
    float radius = 1.5f;
    for (int i = 0; i < 1000; i++) {
        // Gradually change the color from red to brilliant yellow
        float progress = i / 999.0f; 
        float red = 1.0f;
        float green = progress * 1.0f; 
        float blue = progress * 0.1f; 

        glColor4f(red, green, blue, alpha);
        drawCircle(0.0f, 0.0f, radius, 100); // Draw the circle
        
        //does this count for the transparency requirement?
        alpha -= 0.001f; // Decrease opacity 
        radius -= 0.0015f; // Decrease radius for next circle
    }

    // Draw sun, white
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(0.0f, 0.0f, 0.05f, 100);

    drawLand();
    drawHouse(0.6f, -0.7f, 0.6f);
    drawTree(0.0f, -0.7f, 0.6f);
    drawCloud(-0.3f, 0.6f, 0.08f);
    drawCloud(0.7f, 0.2f, 0.12f);
    drawCloud(-0.6f, 0.1f, 0.18f);


    glFlush(); // Render now
}
//------------------------------------------------------------------------------------
// main()
//
// Main function. GLUT runs as a console application starting at main().
//------------------------------------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT.
    glutInitWindowSize(300, 300);          // Set the window's initial width & height.
    glutInitWindowPosition(50, 50);        // Position the window's initial top-left corner.
    glutCreateWindow("OpenGL Hello World");// Create a window with the given title.
    glutDisplayFunc(display);              // Register display callback handler for window re-paint.
    glutMainLoop();                        // Enter the infinitely event-processing loop.
    return 0;
}
