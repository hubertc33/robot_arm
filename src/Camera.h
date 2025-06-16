#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

// Klasa obs³uguj¹ca kamerê w scenie 3D — widok orbitalny (obrót wokó³ œrodka)
class Camera {
public:
    float radius = 40.0f;   // Odleg³oœæ kamery od œrodka sceny
    float theta = 0.0f;     // K¹t obrotu wokó³ osi Y (azymut)
    float phi = 45.0f;      // K¹t elewacji (pion)

    float lastX = 400.0f;   // Pozycja kursora przy poprzednim ruchu
    float lastY = 300.0f;
    bool firstMouse = true; // Czy pierwszy raz poruszono myszk¹
    bool mousePressed = false;  // Czy lewy przycisk myszy jest wciœniêty

    // Obs³uga myszy: ruch, klikniêcie i scroll
    void handleMouseMovement(double xpos, double ypos);
    void handleMouseButton(int button, int action);
    void handleScroll(double yoffset);

    // Podpiêcie callbacków GLFW do okna
    void setView(GLFWwindow* window);
    
    // Obliczenie macierzy widoku (kamera orbituj¹ca)
    glm::mat4 getViewMatrix() const;

    // Callback do zmiany rozdzielczoœci okna
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    glm::vec3 Camera::getCameraPosition() const;
};
