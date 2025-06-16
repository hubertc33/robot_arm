#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"
#include "GuiManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "ShaderProgram.h"

// G³ówna klasa zarz¹dzaj¹ca symulacj¹ i pêtl¹ renderowania
class Simulation {
private:
    GLFWwindow* window = nullptr;   // WskaŸnik na okno GLFW
    Camera camera;                  // Kamera 3D
    GuiManager gui;                 // Interfejs u¿ytkownika (ImGui)
    Scene scene;                    // Logika i obiekty sceny
    ShaderProgram* shader = nullptr;// Shadery do renderingu
    InputManager input;             // Obs³uga wejœcia z klawiatury

public:
    // Uruchamia ca³¹ aplikacjê
    void run();

private:
    // Inicjalizacja GLFW + OpenGL
    bool initLibrary();

    // Tworzy systemy: scenê, GUI, shadery
    void initSystems();

    // G³ówna pêtla renderowania i interakcji
    void mainLoop();

    // Zwalnia zasoby i koñczy program
    void shutdown();
};