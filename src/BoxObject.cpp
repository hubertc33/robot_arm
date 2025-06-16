#include "BoxObject.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// Aktualizacja stanu pude³ka — pozycjonowanie wzglêdem chwytaka
void BoxObject::update(const glm::vec3& gripperPos, const glm::mat4& fullArmTransform, bool isPlayback) {
    // Oblicz dystans miêdzy chwytakiem a pude³kiem
    float distance = glm::length(gripperPos - position);

    // SprawdŸ, czy chwytak w³aœnie zaczyna chwytaæ obiekt bêd¹cy w zasiêgu 
    if ((isGrabbing && !wasGrabbing && distance < 1.5f && !held) ||
        (isPlayback && isGrabbing && distance < 1.5f && !held)) {
        held = true;
    }
    
    // SprawdŸ, czy chwytak puszcza obiekt i obiekt powinien zostaæ od³o¿ony
    if (!isGrabbing && wasGrabbing && held) {
        if (gripperPos.x < -5.0f || gripperPos.x > 5.0f || gripperPos.z < -5.0f || gripperPos.z > 5.0f) {
            held = false;
            position = glm::vec3(modelMatrix * glm::vec4(0, 0, 0, 1));
        }
    }
    // Jeœli obiekt jest trzymany — porusza siê z chwytakiem
    if (held) {
        modelMatrix = fullArmTransform;
    }
    // W przeciwnym razie, pozycjonuj swobodnie z grawitacj¹
    else {
        modelMatrix = glm::translate(glm::mat4(1.0f), position);
        // Symulacja opadania
        if (!isGrabbing && position.y > 2.0f) {
            position.y -= 0.1f;
            modelMatrix = glm::translate(glm::mat4(1.0f), position);
        }
        else if (position.y <= 2.0f) {
            position.y = 2.0f;  // Zatrzymanie na pod³o¿u
        }
    }
}


// Rysowanie pude³ka w scenie 3D
void BoxObject::draw(const glm::mat4& viewProj, const ShaderProgram& shader, Renderer& renderer, Camera& camera) {
    glm::mat4 scaled = modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(2.4f));
    glm::vec3 camPos = camera.getCameraPosition();
    renderer.drawMesh(
        scaled,
        viewProj,
        shader,
        renderer.cubeVAO,
        36,
        glm::vec4(0.8f, 0.8f, 0.2f, 1.0f),
        camPos
    );
}
// Pomocnicza funkcja: oblicz transformacjê chwytaka dla danego zestawu k¹tów
glm::mat4 BoxObject::computeGripperTransform(float joint0, float joint1, float joint2) {
    glm::mat4 result = glm::mat4(1.0f);
    result = glm::rotate(result, glm::radians(joint0), glm::vec3(0.0f, 1.0f, 0.0f));
    result = glm::translate(result, glm::vec3(0.0f, 7.5f, 0.0f));
    result = glm::rotate(result, glm::radians(joint1), glm::vec3(1.0f, 0.0f, 0.0f));
    result = glm::translate(result, glm::vec3(0.0f, 7.0f, 0.0f));
    result = glm::rotate(result, glm::radians(joint2), glm::vec3(1.0f, 0.0f, 0.0f));
    result = glm::translate(result, glm::vec3(0.0f, 8.5f, 0.0f));
    return result;
}
