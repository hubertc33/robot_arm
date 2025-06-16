#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <imgui.h>

// Obs³uga ruchu myszy — obracanie kamery wokó³ œrodka sceny
void Camera::handleMouseMovement(double xpos, double ypos) {
    if (!mousePressed) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float sensitivity = 0.25f;
    float xoffset = (xpos - lastX) * sensitivity;
    float yoffset = (lastY - ypos) * sensitivity;

    lastX = xpos;
    lastY = ypos;

    theta += xoffset; // Obrót poziomy
    phi += yoffset; // Obrót pionowy

    // Ograniczenie k¹ta pionowego, by kamera nie "przewraca³a siê"
    if (phi < 5.0f) phi = 5.0f;
    if (phi > 175.0f) phi = 175.0f;
}
// Obs³uga klikniêcia myszy — aktywacja trybu obracania
void Camera::handleMouseButton(int button, int action) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            mousePressed = true;
            firstMouse = true;
        }
        else if (action == GLFW_RELEASE) {
            mousePressed = false;
        }
    }
}
// Obs³uga scrolla myszy — zmiana oddalenia (zoom kamery)
void Camera::handleScroll(double yoffset) {
    radius -= static_cast<float>(yoffset);
    if (radius < 5.0f) radius = 5.0f;
    if (radius > 100.0f) radius = 100.0f;
}
// Ustawienie callbacków GLFW obs³uguj¹cych mysz i scroll
void Camera::setView(GLFWwindow* window) {
    glfwSetWindowUserPointer(window, this);

    // Ruch myszy
    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) {
        if (!ImGui::GetIO().WantCaptureMouse)
            static_cast<Camera*>(glfwGetWindowUserPointer(w))->handleMouseMovement(x, y);
        });
    
    // Klikniêcie myszy
    glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods) {
        static_cast<Camera*>(glfwGetWindowUserPointer(w))->handleMouseButton(button, action);
        });

    // Scroll myszy (zoom)
    glfwSetScrollCallback(window, [](GLFWwindow* w, double xoffset, double yoffset) {
        static_cast<Camera*>(glfwGetWindowUserPointer(w))->handleScroll(yoffset);
        });

    // Scroll myszy (zoom)
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

// Obliczenie macierzy widoku (ViewMatrix) w oparciu o bie¿¹ce k¹ty i promieñ
glm::mat4 Camera::getViewMatrix() const {
    float camX = radius * sin(glm::radians(phi)) * cos(glm::radians(theta));
    float camY = radius * cos(glm::radians(phi));
    float camZ = radius * sin(glm::radians(phi)) * sin(glm::radians(theta));

    glm::vec3 camPos = glm::vec3(camX, camY, camZ);
    return glm::lookAt(camPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

// Callback: zmiana rozmiaru okna — dostosowanie widoku OpenGL
void Camera::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

glm::vec3 Camera::getCameraPosition() const {
    float camX = radius * sin(glm::radians(phi)) * cos(glm::radians(theta));
    float camY = radius * cos(glm::radians(phi));
    float camZ = radius * sin(glm::radians(phi)) * sin(glm::radians(theta));
    return glm::vec3(camX, camY, camZ);
}