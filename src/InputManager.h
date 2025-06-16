#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

// Deklaracja klas u¿ywanych przez InputManager
class RobotArm;
class IKController;
class BoxObject;
struct GLFWwindow;

// Klasa obs³uguj¹ca sterowanie z klawiatury (ruchy ramienia, chwytanie)
class InputManager {
public:
    // Obs³uga klawiszy steruj¹cych przegubami
    void handleKeyboard(GLFWwindow* window, RobotArm& robot, IKController& ik);
    
    // Obs³uga klawiszy do kontrolowania chwytaka
    void handleGripper(GLFWwindow* window, RobotArm& robot, const glm::vec3& gripperPos);
    
    // Logika wykrywania kolizji chwytaka z pude³kiem i zarz¹dzanie stanem chwytu
    void updateGrabbingState(GLFWwindow* window, BoxObject& cube, const glm::vec3& gripperPos, bool isPlaying);
};
