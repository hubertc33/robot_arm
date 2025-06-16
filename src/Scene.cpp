#include "Scene.h"
#include "InputManager.h"
#include "ShaderProgram.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

// Inicjalizuje elementy sceny: geometrie i pozycjê pude³ka
void Scene::init() {
    renderer.initCylinder();       // walce – do segmentów
    renderer.initGrid();           // siatka pomocnicza
    renderer.initCube();           // kostka
    renderer.initGround();         // pod³oga
    
    cube.position = glm::vec3(0.0f, 0.0f, 10.0f);  // pocz¹tkowa pozycja kostki
}

// Aktualizuje logikê sceny – wejœcia, pozycje, logika chwytania
void Scene::update(InputManager& input, GLFWwindow* window) {
    // zapis stanu przegubu
    prevJoint1 = robot.joint1;
    prevJoint2 = robot.joint2;

    glm::vec3 gripperPos = robot.getGripperPos(); // aktualna pozycja chwytaka

    // Obs³uga wejœcia – klawiatura i chwytak
    input.handleKeyboard(window, robot, ik);
    input.handleGripper(window, robot, gripperPos);
    input.updateGrabbingState(window, cube, gripperPos, recorder.isPlaying);

    // Obliczenie transformacji chwytaka (dla aktualnej pozycji robota)
    glm::mat4 cubeHold = cube.computeGripperTransform(robot.joint0, robot.joint1, robot.joint2);
    
    // Aktualizacja pozycji pude³ka wzglêdem chwytaka
    cube.update(gripperPos, cubeHold,recorder.isPlaying);
}

// Rysuje ca³¹ scenê: pod³ogê, robota, pude³ko i siatkê 
void Scene::draw(const glm::mat4& projection, const glm::mat4& view, ShaderProgram& shader, Camera& camera, bool showGrid) {
    glm::mat4 viewProj = projection * view;
    shader.use();

    renderer.clear();                         // czyœci ekran
    renderer.drawGround(shader, viewProj);    // pod³oga
    robot.draw(projection, view, shader, renderer,camera);  // ramiê robota
    cube.draw(viewProj, shader, renderer, camera);    // pude³ko

    // Rysowanie siatki
    if (this->showGrid) {
        renderer.drawGrid(shader, viewProj);
    }

    // Rysowanie ma³ego zielonego szeœcianu jako punktu docelowego dla IK
    glm::vec3 camPos = camera.getCameraPosition();
    glm::mat4 targetModel = glm::translate(glm::mat4(1.0f), glm::vec3(ik.targetX, ik.targetY, ik.targetZ));
    targetModel = glm::scale(targetModel, glm::vec3(0.3f));
    renderer.drawPoint(targetModel, viewProj, shader, renderer.cubeVAO, 36, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), camPos);
}

// Detekcja kolizji koñcówki ramienia z pod³o¿em
void Scene::handleCollision() {
    glm::vec3 center = glm::vec3(robot.getEndEffectorTransform() * glm::vec4(0.0f, 0.7f, 0.0f, 1.0f));
    float radius = 0.7f;

    // Jeœli koniec ramienia jest za nisko – cofnij przeguby do poprzedniego stanu
    if (center.y - radius < 1.2f) {
        robot.joint1 = prevJoint1;
        robot.joint2 = prevJoint2;
    }
}

// Zwraca bie¿¹c¹ pozycjê chwytaka (przekierowanie do robota)
glm::vec3 Scene::getGripperPos() const {
    return robot.getGripperPos();
}

// Aktualizacja odtwarzania ruchu – wczytywanie kolejnych klatek
void Scene::updatePlayback(float deltaTime) {
    cube.wasGrabbing = cube.isGrabbing;
    recorder.updatePlayback(deltaTime, robot.joint0, robot.joint1, robot.joint2, robot.gripAmount, cube.isGrabbing);  
}

// Aktualizacja nagrywania – zapis aktualnej pozycji robota
void Scene::updateRecording(float deltaTime) {
    if (recorder.isRecording) {
        recorder.updateRecording(deltaTime, robot.joint0, robot.joint1, robot.joint2, robot.gripAmount, cube.isGrabbing);
    }
}
