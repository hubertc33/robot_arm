#include "InputManager.h"

#include "RobotArm.h"
#include "IKController.h"
#include "BoxObject.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <iostream> // do debugu

// Obs³uguje naciœniêcia klawiszy — sterowanie rêczne przegubami
void InputManager::handleKeyboard(GLFWwindow* window, RobotArm& robot, IKController& ik) {
    
    // Obrót joint0
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        ik.cancel();
        robot.joint0 += 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        ik.cancel();
        robot.joint0 -= 0.5f;
    }

    // Obrót joint1
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ik.cancel();
        robot.joint1 -= 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ik.cancel();
        robot.joint1 += 0.5f;
    }

    // Obrót joint2
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        ik.cancel();
        robot.joint2 -= 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        ik.cancel();
        robot.joint2 += 0.5f;
    }

    // Ograniczenia k¹tów przegubów do zakresu [-135, 135]
    robot.joint1 = glm::clamp(robot.joint1, -135.0f, 135.0f);
    robot.joint2 = glm::clamp(robot.joint2, -135.0f, 135.0f);
}

// Obs³uguje otwieranie i zamykanie chwytaka przy u¿yciu spacji
void InputManager::handleGripper(GLFWwindow* window, RobotArm& robot, const glm::vec3& gripperPos) {
    if (gripperPos.x < -5.0f || gripperPos.x > 5.0f || gripperPos.z < -5.0f || gripperPos.z > 5.0f) {
        // Jeœli u¿ytkownik trzyma spacjê — zamykanie chwytaka
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            robot.gripAmount += 0.02f;
        }
        // W przeciwnym razie — otwieranie chwytaka
        else {
            robot.gripAmount -= 0.02f;
        }
        // Ograniczenie wartoœci gripAmount do zakresu [0, 1]
        robot.gripAmount = glm::clamp(robot.gripAmount, 0.0f, 1.0f);
    }
}

// Aktualizuje stan "chwytania" dla obiektu(czy chwytak trzyma pude³ko)
void InputManager::updateGrabbingState(GLFWwindow* window, BoxObject& cube, const glm::vec3& gripperPos, bool isPlaying) {
    if (!isPlaying) {
        if (gripperPos.x < -5.0f || gripperPos.x > 5.0f || gripperPos.z < -5.0f || gripperPos.z > 5.0f) {
            bool previous = cube.isGrabbing;
            cube.isGrabbing = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
            cube.wasGrabbing = previous;
        }
    }
}

