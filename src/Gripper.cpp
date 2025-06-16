#include "Gripper.h"
#include "Renderer.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Konstruktor — przekazuje wskaŸnik do wartoœci zacisku (0.0 - otwarty, 1.0 - zamkniêty)
Gripper::Gripper(float* gripPtr)
    : gripAmount(gripPtr) {}

// Rysowanie chwytaka — belka oraz dwa palce zaciskaj¹ce siê wzglêdem gripAmount
void Gripper::draw(const glm::mat4& viewProj, const ShaderProgram& shader, Renderer& renderer, const Camera& camera) {
    // Belka pozioma
    glm::vec3 camPos = camera.getCameraPosition();

    glm::mat4 baseBlock = glm::translate(parentTransform, glm::vec3(0.0f, 0.5f, 0.0f));
    baseBlock = glm::scale(baseBlock, glm::vec3(7.4f, 0.01f, 1.0f));
    renderer.drawMesh(baseBlock, viewProj, shader, renderer.cubeVAO, 36, { 1.0f, 0.2f, 1.2f, 1.0f },camPos);

    // Lewy palec
    glm::mat4 leftFinger = glm::translate(parentTransform, glm::vec3(-4.0f + 0.8f * (*gripAmount), 0.5f, 0.0f));
    leftFinger = glm::scale(leftFinger, glm::vec3(0.1f, 0.3f, 0.1f));
    renderer.drawMesh(leftFinger, viewProj, shader,  renderer.cylVAO, renderer.cylinderIndices.size(), { 1.0f, 0.2f, 0.2f, 1.0f },camPos);

    // Prawy palec
    glm::mat4 rightFinger = glm::translate(parentTransform, glm::vec3(4.0f - 0.8f * (*gripAmount), 0.5f, 0.0f));
    rightFinger = glm::scale(rightFinger, glm::vec3(0.1f, 0.3f, 0.1f));
    renderer.drawMesh(rightFinger, viewProj, shader, renderer.cylVAO, renderer.cylinderIndices.size(), { 1.0f, 0.2f, 0.2f, 1.0f },camPos);
}

// Zwraca pozycjê centralnego punktu chwytaka — do kolizji lub chwytania
glm::vec3 Gripper::getGripperPosition() const {
    return glm::vec3(parentTransform * glm::vec4(0.0f, 0.6f, 0.0f, 1.0f));
}
