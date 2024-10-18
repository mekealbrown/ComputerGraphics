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
bool smoothLighting = true;  // Flag to toggle smooth lighting

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

    // Set shading model based on smoothLighting flag
    if (smoothLighting) {
        glShadeModel(GL_SMOOTH);
    } else {
        glShadeModel(GL_FLAT);
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
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= n; ++i) {
        int index = i % n;
        const auto& top = topVertices[index];
        const auto& bottom = bottomVertices[index];

        if (!smoothLighting) {
            // For flat shading, we need to specify the normal for each face
            int nextIndex = (index + 1) % n;
            const auto& nextTop = topVertices[nextIndex];
            float faceNormalX = (top.z - nextTop.z);
            float faceNormalZ = -(top.x - nextTop.x);
            float length = sqrt(faceNormalX * faceNormalX + faceNormalZ * faceNormalZ);
            glNormal3f(faceNormalX / length, 0, faceNormalZ / length);
        }

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

    gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

    // Set up lighting
    GLfloat light_position[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    // Set material properties
    GLfloat mat_diffuse[] = { 0.8f, 0.2f, 0.2f, 1.0f };  // Reddish color
    GLfloat mat_ambient[] = { 0.2f, 0.1f, 0.1f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 50.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glRotatef(rotationAngle, 0, 1, 0);

    drawNagonalPrism(32, 1.0f, 2.0f);

    glutSwapBuffers();
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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
        case 'S':
            smoothLighting = !smoothLighting;
            std::cout << (smoothLighting ? "Smooth" : "Flat") << " shading enabled" << std::endl;
            break;
        case 27:  // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("N-agonal Prism with Optional Smooth Lighting");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(0, update, 0);

    std::cout << "Press 'S' to toggle between smooth and flat shading" << std::endl;
    std::cout << "Press 'ESC' to exit" << std::endl;

    glutMainLoop();
    return 0;
}