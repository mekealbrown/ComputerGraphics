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
#include "cylinder.hpp"


struct Vertex {
    float x, y, z;
    Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
};

void drawPrism(int n, float radius, float height, const float color[]) {
    std::vector<Vertex> topVertices;
    std::vector<Vertex> bottomVertices;

    // Generate vertices for top and bottom faces
    for (int i = 0; i < n; ++i) {
        float angle = 2.0f * M_PI * i / n;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        topVertices.emplace_back(x, height / 2, z);
        bottomVertices.emplace_back(x, -height / 2, z);
    }

    // Draw top face
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1, 0);
    for (const auto& vertex : topVertices) {
        glVertex3f(vertex.x, vertex.y, vertex.z);
    }
    glEnd();

    // Draw bottom face
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1, 0);
    for (auto it = bottomVertices.rbegin(); it != bottomVertices.rend(); ++it) {
        glVertex3f(it->x, it->y, it->z);
    }
    glEnd();

    // Draw side faces
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        
        // Calculate normal for the side face
        float nx = topVertices[i].x + topVertices[next].x;
        float nz = topVertices[i].z + topVertices[next].z;
        float length = sqrt(nx*nx + nz*nz);
        nx /= length;
        nz /= length;

        glNormal3f(nx, 0, nz);

        // First triangle
        glVertex3f(topVertices[i].x, topVertices[i].y, topVertices[i].z);
        glVertex3f(bottomVertices[i].x, bottomVertices[i].y, bottomVertices[i].z);
        glVertex3f(topVertices[next].x, topVertices[next].y, topVertices[next].z);

        // Second triangle
        glVertex3f(topVertices[next].x, topVertices[next].y, topVertices[next].z);
        glVertex3f(bottomVertices[i].x, bottomVertices[i].y, bottomVertices[i].z);
        glVertex3f(bottomVertices[next].x, bottomVertices[next].y, bottomVertices[next].z);
    }
    glEnd();
}