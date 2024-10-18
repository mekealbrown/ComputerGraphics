//------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #3: Lighted Prism
// Due date --- October 14, 2024
// 
// Draw an n-agonal prism. The prism will be lighted, with each vertex having
// an associated normal vector, and is movable thanks to David Eck's camera API.
//------------------------------------------------------------------------------


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
#include <algorithm>
#include "camera.h"


//Define Vertex struct and any useful constants
struct Vertex {
    float x, y, z;
};

const float PI = 3.14159265358979323846f;
const float RADIUS = 0.5f;
const float HEIGHT = 0.5f;
const GLfloat CUBE_COLOR[] = { 0.7f, 0.0f, 0.7f, 1.0f };

static int NUM_FACES;
std::vector<Vertex> bottom_face;
std::vector<Vertex> top_face;


/*
* normalVec()
* 
* This function takes points P0, P1, and P2 and computes the vector
* that is normal to the points. It returns the normal vector
*/
Vertex normalVec(const Vertex& p0, const Vertex& p1, const Vertex& p2) {
    Vertex v = {p1.x - p0.x, p1.y - p0.y, p1.z - p0.z};
    Vertex w = {p2.x - p0.x, p2.y - p0.y, p2.z - p0.z};
    
    //Negating? I'm not entirely sure why this fixes things...
    Vertex normal = {
        -(v.y * w.z - v.z * w.y),
        -(v.z * w.x - v.x * w.z),
        -(v.x * w.y - v.y * w.x)
    };
    
    //normalize length
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length != 0) {
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;
    }
    
    return normal;
}

/*
* calcPoints()
*
* This function calculates the points for the top and bottom
* faces of a prism. These can then be used to draw the faces
* and or draw the sides of a prism. The function returns a 
* vector containing all of the vertices.
*/
std::vector<Vertex> calcPoints(int n, float radius, float height) {
    std::vector<Vertex> vertices;
    vertices.reserve(n + 2);
    vertices.push_back({0, height, 0}); // center vertex

    for (int i = 0; i <= n; ++i) {
        float angle = 2.0f * PI * i / n;
        vertices.push_back({
            radius * std::cos(angle),
            height,
            radius * std::sin(angle)
        });
    }

    return vertices;
}

/*
* drawFace()
*
* This function, given some vertices, will draw a face -> :) or :( are not expected outputs
*/
void drawFace(const std::vector<Vertex>& points) {
    glBegin(GL_TRIANGLE_FAN);
    for (const auto& point : points) {
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
}

/*
* drawSides()
*
* This function draws the sides of a prism. It is assumed that the top and bottom
* points have been calculated prior to the calling of this function.
*/
void drawSides() {
    for (int i = 0; i < NUM_FACES; ++i) {
        Vertex normal = normalVec(top_face[i + 1], bottom_face[i + 1], top_face[i + 2]);

        glBegin(GL_TRIANGLES);
        glNormal3f(normal.x, normal.y, normal.z);

        glVertex3f(top_face[i + 1].x, top_face[i + 1].y, top_face[i + 1].z);
        glVertex3f(bottom_face[i + 1].x, bottom_face[i + 1].y, bottom_face[i + 1].z);
        glVertex3f(top_face[i + 2].x, top_face[i + 2].y, top_face[i + 2].z);

        glVertex3f(top_face[i + 2].x, top_face[i + 2].y, top_face[i + 2].z);
        glVertex3f(bottom_face[i + 1].x, bottom_face[i + 1].y, bottom_face[i + 1].z);
        glVertex3f(bottom_face[i + 2].x, bottom_face[i + 2].y, bottom_face[i + 2].z);

        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    cameraSetLimits(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); 
    cameraApply();       

    GLfloat background[] = {1.0f, 0.8f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CUBE_COLOR);
    glMaterialfv(GL_FRONT, GL_SPECULAR, CUBE_COLOR);
    glMaterialfv(GL_FRONT, GL_AMBIENT, background);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    glColor3fv(CUBE_COLOR);
    

    glNormal3f(0.0f, -1.0f, 0.0f);
    drawFace(bottom_face);

    glNormal3f(0.0f, 1.0f, 0.0f);
    drawFace(top_face);

    drawSides();
    
    glFlush();
}

void init() {
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    glClearColor(1.0f, 0.8f, 0.0f, 1.0f); //gold..except it really just looks yellow

    bottom_face = calcPoints(NUM_FACES, RADIUS, 0.0f); //calculate once
    top_face = calcPoints(NUM_FACES, RADIUS, HEIGHT);
}

int main(int argc, char** argv) {
    do {
        std::cout << "Enter number of faces (minimum 3): ";
        std::cin >> NUM_FACES;
    } while (NUM_FACES < 3);

    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lighted N-agonal Prism");
    glutDisplayFunc(display);
    init(); 
    glutMainLoop();
    return 0;
}