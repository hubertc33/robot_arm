#pragma once

#include <glm/glm.hpp>
// Deklaracja klas u¿ywanych wewn¹trz
class ShaderProgram;
class Renderer;
class Camera;
// Klasa reprezentuj¹ca pude³ko, które mo¿e byæ podniesione przez chwytak
class BoxObject {
public:
    glm::vec3 position; // Aktualna pozycja pude³ka
    glm::mat4 modelMatrix = glm::mat4(1.0f); // Transformacja obiektu

    
    bool isGrabbing = false;    // Czy chwytak obecnie œciska
    bool wasGrabbing = false;   // Czy chwytak œciska³ w poprzedniej klatce
    bool held = false;          // Czy pude³ko jest aktualnie trzymane
    // Aktualizuje pozycjê pude³ka w zale¿noœci od chwytaka i symulacji
    void BoxObject::update(const glm::vec3& gripperPos, const glm::mat4& fullArmTransform, bool isPlayback);
    // Rysuje pude³ko na ekranie przy u¿yciu shaderów i renderera
    void draw(const glm::mat4& viewProj, const ShaderProgram& shader, Renderer& renderer, Camera& camera);
    // Oblicza transformacjê koñcówki ramienia na podstawie k¹tów stawów
    glm::mat4 computeGripperTransform(float joint0, float joint1, float joint2);
};
