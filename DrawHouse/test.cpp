#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

float transitionProgress = 0.0f;
bool transitioning = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        transitioning = true;
    }
}

void updateProjectionMatrix(glm::mat4 &projection, float aspectRatio) {
    float nearClip = 0.1f;
    float farClip = 100.0f;
    float fieldOfView = 45.0f;

    float orthoLeft = -1.0f;
    float orthoRight = 1.0f;
    float orthoBottom = -1.0f;
    float orthoTop = 1.0f;

    float left = orthoLeft + (transitionProgress * -5.0f);
    float right = orthoRight + (transitionProgress * 5.0f);
    float bottom = orthoBottom + (transitionProgress * -5.0f);
    float top = orthoTop + (transitionProgress * 5.0f);

    if (transitionProgress < 1.0f) {
        projection = glm::ortho(left, right, bottom, top, nearClip, farClip);
    } else {
        projection = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClip, farClip);
    }
}

void updateViewMatrix(glm::mat4 &view) {
    if (transitionProgress < 1.0f) {
        float panX = transitionProgress * 2.0f;
        float panY = transitionProgress * 2.0f;
        view = glm::translate(glm::mat4(1.0f), glm::vec3(-panX, -panY, 0.0f));
    } else {
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    }
}

void renderScene(const glm::mat4 &projection, const glm::mat4 &view) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Simple rendering example: a colored square or cube
    // Set up your shader program and pass matrices to it

    // This is a placeholder for actual rendering code
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "2D to 3D Transition", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Projection and view matrices
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window)) {
        // Update transition progress
        if (transitioning) {
            transitionProgress += 0.01f; // Adjust speed as needed
            if (transitionProgress >= 1.0f) {
                transitionProgress = 1.0f;
                transitioning = false;
            }
        }

        // Update matrices
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspectRatio = static_cast<float>(width) / height;
        updateProjectionMatrix(projection, aspectRatio);
        updateViewMatrix(view);

        // Render the scene
        renderScene(projection, view);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
