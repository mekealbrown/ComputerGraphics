//-------------------------------------------------------------------------------
// Developer -- Mekeal Brown
// Course ----- CS3233
// Project ---- Homework #6: Take that!
// Due Date --- November 13, 2024
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
    //Vector3 normalize()
    //{
    //    float len = sqrt(x*x + y*y + z*z);
    //    return Vector3(x/len, y/len, z/len);
    //}
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
    return Vector3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);//.normalize();
}

//-------------------------------------------------------------------------------
// drawPrism()
//
// This function draws an n-agonal prism.
//-------------------------------------------------------------------------------
void drawPrism(int n, float radius, float height, const float color[], bool textured) 
{
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.0f);
    
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

	if(textured){
		glEnable(GL_TEXTURE_2D);
	}
  

  // top face
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0f, 1.0f, 0.0f);
    
  // Center vertex
	if(textured){
		glTexCoord2f(0.5f, 0.5f);
	}
  
  glVertex3f(0.0f, height / 2, 0.0f);
    
	//calculate tex coords
  for(int i = 0; i <= n; ++i) {  
    int idx = i % n;
    float angle = 2.0f * M_PI * idx / n;

		if(textured){
    	float tx = cos(angle) * 0.5f + 0.5f;
    	float ty = sin(angle) * 0.5f + 0.5f;
    	glTexCoord2f(tx, ty);
		}

		glVertex3f(topVertices[idx].x, topVertices[idx].y, topVertices[idx].z);
  }
  glEnd();

	if(textured){
		glDisable(GL_TEXTURE_2D);
	}

  // bottom face
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0.0f, -1.0f, 0.0f);
  for(const auto& vertex : bottomVertices) {
    glVertex3f(vertex.x, vertex.y, vertex.z);
  }
  glEnd();

  // side faces
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
// drawDrCrawleyBoard()
//
// This function draws a cylindrical prism with a texture mapping of the esteemed
// Dr. Crawley.
//-------------------------------------------------------------------------------
void drawDrCrawleyBoard(int n, float radius, float height, const float color[])
{
  drawPrism(n, radius, height, color, 1);
}

//-------------------------------------------------------------------------------
// drawDart()
//
// This function draws a dart
//-------------------------------------------------------------------------------
void drawDart(float size)
{
    glPushMatrix();
      glScalef(size, size, size);
			glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

      drawPyramid(4, 0.01f, 0.03f, PURPLE);
      
			glPushMatrix();
				glTranslatef(0.0f, -0.02f, 0.0f);
      	drawPrism(360, 0.003f, 0.06f, PURPLE, 0);
			glPopMatrix();

    glPopMatrix();
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
    
    glColor3fv(PURPLE);  
    
    glRasterPos3f(0, 0, 0);
    for(const char* c = text; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glEnable(GL_LIGHTING);
    glPopMatrix();
}


