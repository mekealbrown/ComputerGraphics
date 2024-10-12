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


struct Vertex {
    float x, y, z;
};

void initVertex(Vertex *v, float x, float y, float z)
{
    v->x = x; 
    v->y = y; 
    v->z = z;
}


std::vector<Vertex> calcPoints(int n, float radius, float centerX, float centerY, float centerZ, bool top) {
    std::vector<Vertex> vertices;
    Vertex v;
    initVertex(&v, centerX, centerY, centerZ);

    vertices.push_back(v); //push center vertex
    for (int i = 0; i < n; ++i) {
        float angle = top ? 2.0f * M_PI * i / n : -2.0f * M_PI * i / n; // reverse drawing order if bottom face

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

Vertex calcTransVertex(const Vertex& original, float x, float y, float z)
{
    Vertex new_vert;
    initVertex(&new_vert, (original.x - x), (original.y - y), (original.z - z));
    return new_vert;
}

Vertex calcNormalVec(const Vertex& p0, const Vertex& p1, const Vertex& p2)
{
    //translate p0 to 0,0,0
    Vertex trans_p0 = calcTransVertex(p0, p0.x, p0.y, p0.z); 
    std::cout << "trans_p0 " << trans_p0.x << " " << trans_p0.y << " " << trans_p0.z << "\n";
    Vertex trans_p1 = calcTransVertex(p1, p0.x, p0.y, p0.z); 
    std::cout << "trans_p1 " << trans_p1.x << " " << trans_p1.y << " " << trans_p1.z << "\n";
    Vertex trans_p2 = calcTransVertex(p2, p0.x, p0.y, p0.z);
    std::cout << "trans_p2 " << trans_p2.x << " " << trans_p2.y << " " << trans_p2.z << "\n\n";


    Vertex normal;

    normal.x = (trans_p1.y * trans_p2.x) - (trans_p1.z * trans_p2.y);
    normal.y = (trans_p1.z * trans_p2.x) - (trans_p1.x * trans_p2.z);
    normal.z = (trans_p1.x * trans_p2.y) - (trans_p1.y * trans_p2.x);

    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length != 0) { // Avoid division by zero
        normal.x /= length;
        normal.y /= length;
        normal.z /= length;
    }

    return normal;
    //calculate
}

void drawPrism(int n, const std::vector<Vertex>& points)
{
    Vertex norm;
    glBegin(GL_TRIANGLE_FAN);
        for(int j = 0; j < n; j++){
            norm = calcNormalVec(points[0], points[j + 1], points[j + 2]);
            glNormal3f(norm.x, norm.y, norm.z);

            for(int i = 0; i < 3; i++){
                //std::cout << points[j + i].x << " " <<  points[j + i].y << " " << points[j + i].z << "\n";
                glVertex3f(points[j + i].x, points[j + i].y, points[j + i].z);
            }
        }
    glEnd();
}

void drawSides(int n, const std::vector<Vertex>& top, std::vector<Vertex>& bottom)
{
    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 0; i < n; i++){
            glVertex3f(top[i + 1].x, top[i + 1].y, top[i + 1].z);
            glVertex3f(bottom[i + 1].x, bottom[i + 1].y, bottom[i + 1].z);
            glVertex3f(top[i + 2].x, top[i + 2].y, top[i + 2].z);
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

    GLfloat lineColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, lineColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, lineColor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, lineColor);
    
    // Draw X-axis
    glBegin(GL_LINES);
    glVertex3f(-1.0f, 0.0f, 0.0f); // X-
    glVertex3f(1.0f, 0.0f, 0.0f);  // X+
    glEnd();
    
    // Draw Y-axis
    glBegin(GL_LINES);
    glVertex3f(0.0f, -1.0f, 0.0f); // Y-
    glVertex3f(0.0f, 1.0f, 0.0f);  // Y+
    glEnd();
    
    // Draw Z-axis
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -1.0f); // Z-
    glVertex3f(0.0f, 0.0f, 1.0f);  // Z+
    glEnd();

    int n = 6;

    GLfloat cube_color[] = { 0.7f, 0.0f, 0.7f, 1.0f };   // Go Bisons!
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    
    std::vector<Vertex> bottom_face = calcPoints(6, 0.5f, 0.0f, 0.0f, 0.0f, 0);
    drawPrism(6, bottom_face);

    std::vector<Vertex> top_face = calcPoints(6, 0.5f, 0.0f, 0.0f, 0.5f, 1);
    drawPrism(6, top_face);

    drawSides(6, bottom_face, top_face);
    
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
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Unit Cube With Rotation");
    glutDisplayFunc(display);
	init(); 
    glutMainLoop();
    return 0;
}
