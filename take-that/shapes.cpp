//-------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #5: Awesome Sauce
// Due Date --- November 1, 2024
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
#include "shapes.h"


//-------------------------------------------------------------------------------
// struct TexCoord2d
//
// This struct is used to define a 2d texture coordinate pair
//
// normalize()
//
// This function normalizes the texture coordinates to unit length.
//-------------------------------------------------------------------------------
struct TexCoord2d {
    float s, t;
    TexCoord2d(float s, float t) : s(s), t(t) {}
    TexCoord2d normalize()
    {
        return TexCoord2d(s / TEX_WIDTH, t / TEX_HEIGHT);
    }
};


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
    glMaterialfv(GL_FRONT, GL_AMBIENT, BLACK);
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
            glMaterialfv(GL_FRONT, GL_AMBIENT, BLACK);
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

//-------------------------------------------------------------------------------
// drawTabascoBox()
//
// This function draws a rectangular prism and then texturizes it with a Tabasco
// sauce box
//-------------------------------------------------------------------------------
void drawTabascoBox(float size)
{
    glPushMatrix();
    glScalef(size, size, size);

    //box coords
    float point[][3] = {
        {0, 0, 0},   
        {0, 0, 1.0f}, 
        {1.0f, 0, 0}, 
        {1.0f, 0, 1.0f}, 
        {0, 3.0f, 0},   
        {0, 3.0f, 1.0f}, 
        {1.0f, 3.0f, 0}, 
        {1.0f, 3.0f, 1.0f} 
    };

    //texture coords
    //I'll be honest, I don't fully grasp this. 99% of these
    //points were guesses until I got something that was "close enough".
    TexCoord2d t_points[] = {
        //front face
        TexCoord2d(0, 0),
        TexCoord2d(0, 2048),
        TexCoord2d(428, 2048),
        TexCoord2d(428, 0),

        //right side face
        TexCoord2d(428, 0),
        TexCoord2d(428, 2048),
        TexCoord2d(853, 2048),
        TexCoord2d(853, 0),

        //back side face
        TexCoord2d(853, 0),
        TexCoord2d(853, 2048),
        TexCoord2d(1278, 2048),
        TexCoord2d(1278, 0),

        //left side face
        TexCoord2d(1278, 0),
        TexCoord2d(1278, 2048),
        TexCoord2d(1703, 2048),
        TexCoord2d(1703, 0),

        //top face
        TexCoord2d(1725, 0),
        TexCoord2d(1725, 591),
        TexCoord2d(2130, 591),
        TexCoord2d(2130, 0),

        //bottom face
        TexCoord2d(1725, 680),
        TexCoord2d(1725, 1180),
        TexCoord2d(2130, 1180),
        TexCoord2d(2130, 680),
    };

    for(int i = 0; i < 24; i++){
        t_points[i] = t_points[i].normalize();
    }


    float cube_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    glEnable(GL_TEXTURE_2D);

    // Front face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0, 0.0, 1.0); 
        glTexCoord2f(t_points[1].s, t_points[1].t); glVertex3fv(point[1]); 
        glTexCoord2f(t_points[2].s, t_points[2].t); glVertex3fv(point[3]); 
        glTexCoord2f(t_points[3].s, t_points[3].t); glVertex3fv(point[7]); 
        glTexCoord2f(t_points[0].s, t_points[0].t); glVertex3fv(point[5]); 
    glEnd();

    // Back face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0, 0.0, -1.0); 
        glTexCoord2f(t_points[10].s, t_points[10].t); glVertex3fv(point[0]); 
        glTexCoord2f(t_points[9].s, t_points[9].t); glVertex3fv(point[2]); 
        glTexCoord2f(t_points[8].s, t_points[8].t); glVertex3fv(point[6]); 
        glTexCoord2f(t_points[11].s, t_points[11].t); glVertex3fv(point[4]); 
    glEnd();

    // Right face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(1.0, 0.0, 0.0); 
        glTexCoord2f(t_points[5].s, t_points[5].t); glVertex3fv(point[3]); 
        glTexCoord2f(t_points[6].s, t_points[6].t); glVertex3fv(point[2]); 
        glTexCoord2f(t_points[7].s, t_points[4].t); glVertex3fv(point[6]); 
        glTexCoord2f(t_points[4].s, t_points[4].t); glVertex3fv(point[7]); 
    glEnd();

    // Left face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(-1.0, 0.0, 0.0); 
        glTexCoord2f(t_points[13].s, t_points[13].t); glVertex3fv(point[0]); 
        glTexCoord2f(t_points[14].s, t_points[14].t); glVertex3fv(point[1]); 
        glTexCoord2f(t_points[15].s, t_points[15].t); glVertex3fv(point[5]); 
        glTexCoord2f(t_points[12].s, t_points[12].t); glVertex3fv(point[4]); 
    glEnd();

    // Top face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0, 1.0, 0.0); 
        glTexCoord2f(t_points[16].s, t_points[16].t); glVertex3fv(point[4]); 
        glTexCoord2f(t_points[17].s, t_points[17].t); glVertex3fv(point[5]); 
        glTexCoord2f(t_points[18].s, t_points[18].t); glVertex3fv(point[7]); 
        glTexCoord2f(t_points[19].s, t_points[19].t); glVertex3fv(point[6]); 
    glEnd();

    // Bottom face
    glBegin(GL_TRIANGLE_FAN);
        glNormal3f(0.0, -1.0, 0.0); 
        glTexCoord2f(t_points[21].s, t_points[21].t); glVertex3fv(point[0]); 
        glTexCoord2f(t_points[22].s, t_points[22].t); glVertex3fv(point[2]); 
        glTexCoord2f(t_points[23].s, t_points[23].t); glVertex3fv(point[3]); 
        glTexCoord2f(t_points[20].s, t_points[20].t); glVertex3fv(point[1]); 
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawDrCrawleyBoard(int n, float radius, float height, const float color[])
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    //glRotatef(80, 1.0f, 0.0f, 0.0f);
    //glRotatef(30, 0.0f, 0.0f, 1.0f);
    
    std::vector<Vector3> topVertices;
    std::vector<Vector3> bottomVertices;
    
    // vertices for top and bottom faces
    for(int i = 0; i < n; ++i) {
        float angle = 2.0f * M_PI * i / n;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        topVertices.emplace_back(x, height / 2, z);
        bottomVertices.emplace_back(x, -height / 2, z);
    }

    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, BLACK);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    // Enable texture mapping for top face
    glEnable(GL_TEXTURE_2D);

    // top face (textured)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    
    // Center vertex
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0.0f, height / 2, 0.0f);
    
    // Outer vertices with texture coordinates
    for(int i = 0; i <= n; ++i) {  // Note: <= to complete the circle
        int idx = i % n;
        // Calculate texture coordinates to map the texture in a circular pattern
        float angle = 2.0f * M_PI * idx / n;
        float tx = cos(angle) * 0.5f + 0.5f;  // Transform from [-1,1] to [0,1]
        float ty = sin(angle) * 0.5f + 0.5f;  // Transform from [-1,1] to [0,1]
        
        glTexCoord2f(tx, ty);
        glVertex3f(topVertices[idx].x, topVertices[idx].y, topVertices[idx].z);
    }
    glEnd();

    // Disable texture mapping for other faces
    glDisable(GL_TEXTURE_2D);

    // bottom face (untextured)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f);
    for(const auto& vertex : bottomVertices) {
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();

    // side faces (untextured)
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < n; ++i) {
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

    glPopMatrix();
}

void drawDart(float size)
{
    glPushMatrix();
    glScalef(size, size, size);
    glTranslatef(0.0f, 0.3f, 0.0f);

    drawPyramid(4, 0.01f, 0.03f, PURPLE);
    drawPrism(360, 0.003f, 0.06f, PURPLE);

    glPopMatrix();
}


