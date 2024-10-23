//-------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #4: Lighted Scene
// Due Date --- October 23, 2024
//
// Function definitions of helpful drawing functions declared in 'shapes.hpp'
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

#include <vector>
#include <array>
#include <cmath>
#include "shapes.hpp"


//-------------------------------------------------------------------------------
// struct Vector3
//
// This struct is used to define a 3D vector.
//
// normalize()
//
// This function is called after calculating the vector normals in order to 
// normalize the computed result.
//-------------------------------------------------------------------------------
struct Vector3 
{
    float x, y, z;
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    Vector3 normalize()
    {
        float len = sqrt(x*x + y*y + z*z);
        return Vector3(x/len, y/len, z/len);
    }
};

//-------------------------------------------------------------------------------
// calculateNormal()
//
// This function calculates the normal vector for a vertex given the three 
// vertices(p0, p1, p2) that make up the 'W' and 'V' lines.
//-------------------------------------------------------------------------------
Vector3 calculateNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3) 
{
    Vector3 a(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
    Vector3 b(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
    return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x).normalize();
}

//-------------------------------------------------------------------------------
// drawPrism()
//
// This function draws an n-agonal prism.
//-------------------------------------------------------------------------------
void drawPrism(int n, float radius, float height, const float color[]) 
{
    std::vector<Vector3> topVertices;
    std::vector<Vector3> bottomVertices;

    // vertices for top and bottom faces
    for(int i = 0; i < n; ++i){
        float angle = 2.0f * M_PI * i / n;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        topVertices.emplace_back(x, height / 2, z);
        bottomVertices.emplace_back(x, -height / 2, z);
    }

    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, BACKGROUND_COLOR);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
   // glColor3fv(PURPLE);

    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, 1.0f, 0.0f);
        for(const auto& vertex : topVertices){
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
    glEnd();

    // bottom face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0f, -1.0f, 0.0f);
        for(const auto& vertex : bottomVertices){
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
    glEnd();

    // side faces
    glBegin(GL_TRIANGLES);
        for(int i = 0; i < n; ++i){
            int next = (i + 1) % n;
            Vector3 normal = calculateNormal(bottomVertices[i], topVertices[i], topVertices[next]);
            glNormal3f(normal.x, normal.y, normal.z);

            glVertex3f(bottomVertices[i].x, bottomVertices[i].y, bottomVertices[i].z);
            glVertex3f(topVertices[i].x, topVertices[i].y, topVertices[i].z);
            glVertex3f(topVertices[next].x, topVertices[next].y, topVertices[next].z);

            glVertex3f(bottomVertices[i].x, bottomVertices[i].y, bottomVertices[i].z);
            glVertex3f(topVertices[next].x, topVertices[next].y, topVertices[next].z);
            glVertex3f(bottomVertices[next].x, bottomVertices[next].y, bottomVertices[next].z);
        }
    glEnd();
}

//---------------------------------------------------------------------------------
// drawPyramid()
//
// This function draws a 'sides' sided pyramid. The apex is controlled by 'height'.
//---------------------------------------------------------------------------------
void drawPyramid(const int sides, const float radius, const float height, const float color[]) 
{
    std::vector<Vector3> baseVertices;

    // calculate vertices
    for(int i = 0; i < sides; i++){
        float angle = 2.0f * PI * i / sides;
        baseVertices.push_back(Vector3(radius * cos(angle), 0, radius * sin(angle)));
    }

    Vector3 Apex(0, height, 0);

    glBegin(GL_TRIANGLES);
        for(int i = 0; i < sides; i++){
            Vector3 v1 = baseVertices[i];
            Vector3 v2 = baseVertices[(i + 1) % sides];
            Vector3 normal = calculateNormal(v1, v2, Apex);
            if(height > 0){
                normal.x *= -1; normal.y *= -1; normal.z *= -1;
            }
            
            glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
            glMaterialfv(GL_FRONT, GL_SPECULAR, color);
            glMaterialfv(GL_FRONT, GL_AMBIENT, BACKGROUND_COLOR);
            glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
            glColor3fv(color);

            glNormal3f(normal.x, normal.y, normal.z);
            glVertex3f(Apex.x, Apex.y, Apex.z);
            glVertex3f(v1.x, v1.y, v1.z);
            glVertex3f(v2.x, v2.y, v2.z);
        }
    glEnd();
}

//-------------------------------------------------------------------------------
// drawText()
//
// This function is used to draw text into the scene. Doesn't like punctuation 
// characters.
//-------------------------------------------------------------------------------
void drawText(float x, float y, float z, const char* text) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glDisable(GL_LIGHTING);
    
    float modelview[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
    
    // Create a rotation matrix to make text face the camera
    modelview[0] = 1.0f;
    modelview[1] = 0.0f;
    modelview[2] = 0.0f;
    modelview[4] = 0.0f;
    modelview[5] = 1.0f;
    modelview[6] = 0.0f;
    modelview[8] = 0.0f;
    modelview[9] = 0.0f;
    modelview[10] = 1.0f;
    
    glLoadMatrixf(modelview);
    
    glColor3fv(PURPLE);  
    
    glRasterPos3f(0, 0, 0);
    for(const char* c = text; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glEnable(GL_LIGHTING);
    glPopMatrix();
}

