#include <GL/glut.h>
#include <vector>
#include <random>
#include <ctime>

// Structure to represent a raindrop
struct Raindrop {
    float x, y;        // Position
    float speed;       // Falling speed
    float length;      // Length of the raindrop
};

// Global variables
std::vector<Raindrop> raindrops;
const int NUM_RAINDROPS = 1000;
const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;

// Random number generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> xPos(0, WINDOW_WIDTH);
std::uniform_real_distribution<float> yPos(0, WINDOW_HEIGHT);
std::uniform_real_distribution<float> speedDist(5.0f, 15.0f);
std::uniform_real_distribution<float> lengthDist(10.0f, 20.0f);

// Initialize a raindrop with random values
void initRaindrop(Raindrop& drop, bool randomY = true) {
    drop.x = xPos(gen);
    drop.y = randomY ? yPos(gen) : WINDOW_HEIGHT;
    drop.speed = speedDist(gen);
    drop.length = lengthDist(gen);
}

// Initialize the rain system
void initRain() {
    raindrops.resize(NUM_RAINDROPS);
    for (auto& drop : raindrops) {
        initRaindrop(drop);
    }
}

// Update raindrop positions
void update() {
    for (auto& drop : raindrops) {
        // Move the raindrop down
        drop.y -= drop.speed;
        
        // If raindrop goes below screen, reset it to top
        if (drop.y + drop.length < 0) {
            initRaindrop(drop, false);
        }
    }
    glutPostRedisplay();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Set color to light blue
    glColor4f(0.8f, 0.8f, 1.0f, 0.5f);
    
    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Draw raindrops as lines
    glBegin(GL_LINES);
    for (const auto& drop : raindrops) {
        glVertex2f(drop.x, drop.y);
        glVertex2f(drop.x, drop.y + drop.length);
    }
    glEnd();
    
    glDisable(GL_BLEND);
    glutSwapBuffers();
}

// Reshape function
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}

// Timer function for animation
void timer(int value) {
    update();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Animated Rain");
    
    // Set background color to dark blue
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    
    initRain();
    
    glutMainLoop();
    return 0;
}