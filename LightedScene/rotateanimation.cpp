#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <iostream>

struct Vertex {
    float x, y, z;
    float nx, ny, nz;
    Vertex(float x, float y, float z, float nx, float ny, float nz) 
        : x(x), y(y), z(z), nx(nx), ny(ny), nz(nz) {}
};

float rotationAngle = 0.0f;
int lastTime = 0;

void drawNagonalPrism(int n, float radius, float height) {
    std::vector<Vertex> topVertices;
    std::vector<Vertex> bottomVertices;

    for (int i = 0; i < n; ++i) {
        float angle = 2.0f * M_PI * i / n;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        float nx = cos(angle);
        float nz = sin(angle);

        topVertices.emplace_back(x, height / 2, z, nx, 0, nz);
        bottomVertices.emplace_back(x, -height / 2, z, nx, 0, nz);
    }

    glColor3f(1.0f, 0.0f, 0.0f);  // Set color to red for visibility

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
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= n; ++i) {
        int index = i % n;
        const auto& top = topVertices[index];
        const auto& bottom = bottomVertices[index];

        glNormal3f(top.nx, top.ny, top.nz);
        glVertex3f(top.x, top.y, top.z);
        
        glNormal3f(bottom.nx, bottom.ny, bottom.nz);
        glVertex3f(bottom.x, bottom.y, bottom.z);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Move the camera back a bit
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    // Apply rotation
    glRotatef(rotationAngle, 0, 1, 0);

    // Draw coordinate axes for reference
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // X axis in red
    glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
    glColor3f(0.0f, 1.0f, 0.0f); // Y axis in green
    glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
    glColor3f(0.0f, 0.0f, 1.0f); // Z axis in blue
    glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
    glEnd();

    // Draw the prism
    drawNagonalPrism(6, 1.0f, 2.0f);

    glutSwapBuffers();

    // Debug output
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << error << std::endl;
    }
}

void update(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    rotationAngle += 30.0f * deltaTime;
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    lastTime = currentTime;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating N-agonal Prism");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(0, update, 0);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    glutMainLoop();
    return 0;
}