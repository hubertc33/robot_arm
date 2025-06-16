#include <glad/glad.h> 
#include "Simulation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

// G³ówna funkcja – uruchamia ca³¹ symulacjê
void Simulation::run() {
    if (!initLibrary()) return;  // Inicjalizacja GLFW i GLAD
    initSystems();               // Inicjalizacja GUI i sceny
    mainLoop();                  // G³ówna pêtla renderuj¹ca i steruj¹ca
    shutdown();                  // Zwolnienie zasobów
}

// Inicjalizacja bibliotek GLFW, OpenGL i GLAD
bool Simulation::initLibrary() {
    if (!glfwInit()) {
        std::cerr << "Nie udalo sie zainicjalizowac GLFW\n";
        return false;
    }

    // Ustawienia kontekstu OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    // Tworzenie okna
    window = glfwCreateWindow(800, 600, "Robot Arm 3D", nullptr, nullptr);
    if (!window) {
        std::cerr << "Nie udalo sie utworzyc okna GLFW\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Nie udalo sie zaladowac GLAD\n";
        return false;
    }

    glEnable(GL_MULTISAMPLE);   // W³¹cz antyaliasing
    glEnable(GL_DEPTH_TEST);    // W³¹cz test g³êbokoœci (3D)

    return true;
}

// Inicjalizacja kamery, GUI, shaderów i sceny
void Simulation::initSystems() {
    camera.setView(window);                                  // Ustawienie widoku kamery
    gui.init(window);                                        // Inicjalizacja ImGui
    shader = new ShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl"); // £adowanie shaderów
    scene.init();                                            // Inicjalizacja obiektów sceny
}

// G³ówna pêtla aplikacji – logika, GUI i rysowanie
void Simulation::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // Obs³uga wejœæ

        // Logika sceny
        scene.update(input, window);
        scene.updateRecording(ImGui::GetIO().DeltaTime);
        scene.updatePlayback(ImGui::GetIO().DeltaTime);
        scene.handleCollision();

        // Macierze renderingu
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);

        // GUI
        gui.beginFrame();
        gui.draw(scene.robot, scene.ik, scene.recorder, scene.getGripperPos(), scene.showGrid);

        // Rysowanie
        scene.draw(projection, view, *shader,camera, scene.showGrid);

        gui.endFrame();
        glfwSwapBuffers(window);
    }
}

// Zwolnienie wszystkich zasobów po zamkniêciu aplikacji
void Simulation::shutdown() {
    // Usuniêcie buforów i VAO dla pod³o¿a
    glDeleteVertexArrays(1, &scene.renderer.groundVAO);
    glDeleteBuffers(1, &scene.renderer.groundVBO);
   
    // Usuniêcie programu shaderowego
    glDeleteProgram(shader->id);
    delete shader;

    // Zamkniêcie okna i zakoñczenie GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
    
    // Zakoñczenie dzia³ania ImGui
    gui.shutdown();
}
