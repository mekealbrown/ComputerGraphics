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
#include <iostream>

#include "camera.h"  

static int NUM_FACES;


struct Vertex {
    float x, y, z;
};

void initVertex(Vertex *v, float x, float y, float z)
{
    v->x = x; 
    v->y = y; 
    v->z = z;
}


std::vector<Vertex> calcPoints(int n, float radius, float centerX, float centerY, float centerZ) {
    std::vector<Vertex> vertices;
    Vertex v;
    initVertex(&v, centerX, centerY, centerZ);

    vertices.push_back(v); //push center vertex
    for (int i = 0; i < n; ++i) {
        float angle = 2.0f * M_PI * i / n;

        v.x = centerX + radius * cos(angle);
        v.y = centerY + radius * sin(angle);
        v.z = centerZ;

        vertices.push_back(v);
    }
    v.x = centerX + radius * cos(0);
    v.y = centerY + radius * sin(0);
    v.z = centerZ;
    vertices.push_back(v); // Close the fan

    return vertices;
}

//figure out normal vector calculation

Vertex crossProduct(const Vertex& v, const Vertex& w) {

    return {
        v.y * w.z - v.z * w.y,
        v.z * w.x - v.x * w.z,
        v.x * w.y - v.y * w.x
    };
}

void drawPrism(int n, const std::vector<Vertex>& points)
{
    glBegin(GL_TRIANGLE_FAN);
        for(int j = 0; j < n; j++){
            for(int i = 0; i < 3; i++){
                glVertex3f(points[j + i].x, points[j + i].y, points[j + i].z);
            }
        }
    glEnd();
}

void drawSides(int n, const std::vector<Vertex>& top, std::vector<Vertex>& bottom)
{
    Vertex normal;
    glBegin(GL_TRIANGLES);
        for(int i = 0; i < n; i++){
            
            //std::cout << "normal vector: x= " << normal.x << " y= " << normal.y << " z= " << normal.z << "\n"; 

            glVertex3f(top[i + 1].x, top[i + 1].y, top[i + 1].z);
            glVertex3f(bottom[i + 1].x, bottom[i + 1].y, bottom[i + 1].z);
            glVertex3f(top[i + 2].x, top[i + 2].y, top[i + 2].z);

            glVertex3f(top[i + 2].x, top[i + 2].y, top[i + 2].z);
            glVertex3f(bottom[i + 1].x, bottom[i + 1].y, bottom[i + 1].z);
            glVertex3f(bottom[i + 2].x, bottom[i + 2].y, bottom[i + 2].z);
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
	
    cameraSetLimits(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
    cameraApply();       


    GLfloat cube_color[] = { 0.7f, 0.0f, 0.7f, 1.0f };   // Go Bisons!
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    glColor3fv(cube_color);
    
    std::vector<Vertex> bottom_face = calcPoints(NUM_FACES, 0.5f, 0.0f, 0.0f, 0.0f);
    glNormal3i(0, 0, -10);
    drawPrism(NUM_FACES, bottom_face);

    std::vector<Vertex> top_face = calcPoints(NUM_FACES, 0.5f, 0.0f, 0.0f, 0.5f);
    glNormal3i(0, 0, 10);
    drawPrism(NUM_FACES, top_face);

    drawSides(NUM_FACES, bottom_face, top_face);
    
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);      // Turn on a light. Use default light attributes.
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals

    return;
}

//------------------------------------------------------------------------------------
// main()
//
// Main function. GLUT initalizations and the main event loop.
//------------------------------------------------------------------------------------

int main(int argc, char** argv) {
    NUM_FACES = 0;
    while(NUM_FACES < 3){
        std::cout << "Enter n: ";
        std::cin >> NUM_FACES;
    }

    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Unit Cube With Rotation");
    glutDisplayFunc(display);
	init(); 
    glutMainLoop();
    return 0;
}
