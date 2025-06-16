#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

// Deklaracje klas u¿ywanych przez GUI
class RobotArm;
class IKController;
class Recorder;

// Klasa zarz¹dzaj¹ca interfejsem GUI z u¿yciem ImGui
class GuiManager {
public:
    // Inicjalizacja i zamkniêcie ImGui
    void init(GLFWwindow* window);
    void shutdown();
    
    // Zarz¹dzanie klatkami GUI (pocz¹tek i koniec rysowania)
    void beginFrame();
    void endFrame();

    // Rysuje panel GUI do sterowania ramieniem, IK i nagrywaniem
    void draw(RobotArm& robot, IKController& ik, Recorder& recorder,
        const glm::vec3& gripperPos, bool& showGrid);
};
