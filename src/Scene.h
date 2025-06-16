#pragma once

#include "RobotArm.h"
#include "BoxObject.h"
#include "Renderer.h"
#include "Recorder.h"
#include "IKController.h"

#include <glm/glm.hpp>

// Deklaracje klas
class InputManager;
class ShaderProgram;
class Camera;
struct GLFWwindow;


// Klasa odpowiadaj¹ca za logikê, rysowanie i interakcjê sceny
class Scene {
public:
    // Kluczowe komponenty sceny
    RobotArm robot;         // Ramiê robota
    BoxObject cube;         // Obiekt (pude³ko) do chwytania
    Renderer renderer;      // Rysowanie geometrii
    Recorder recorder;      // Nagrywanie i odtwarzanie ruchów
    IKController ik;        // Sterowanie odwrotne (Inverse Kinematics)


    bool showGrid = false; // Czy wyœwietlaæ siatkê w scenie

    // Inicjalizacja zasobów i pozycji
    void init();
    
    // Aktualizacja logiki (wejœcie, ruchy, chwytanie)
    void update(InputManager& input, GLFWwindow* window);
    
    // Rysowanie ca³ej sceny
    void draw(const glm::mat4& projection, const glm::mat4& view, ShaderProgram& shader, Camera& camera, bool showGrid);
    
    // Rysowanie ca³ej sceny
    void handleCollision();
    
    // Zwraca bie¿¹c¹ pozycjê chwytaka
    glm::vec3 getGripperPos() const;
    
    // Aktualizuje odtwarzanie nagrania
    void updatePlayback(float deltaTime);
    
    // Zapisuje aktualny stan do nagrania
    void updateRecording(float deltaTime);

private:
    // Poprzednie wartoœci przegubów (do detekcji zmian)
    float prevJoint1 = 0.0f;
    float prevJoint2 = 0.0f;
};
