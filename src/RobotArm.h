#pragma once

#include <glm/glm.hpp>
#include "Segment.h"
#include "Gripper.h"

class ShaderProgram;
class Renderer;
class Camera;

// Klasa reprezentuj¹ca ramiê robota z³o¿one z przegubów i segmentów
class RobotArm {
public:
    // K¹ty obrotu przegubów (w stopniach)
    float joint0 = 0.0f;
    float joint1 = 0.0f;
    float joint2 = 0.0f;
    
    // Poziom zacisku chwytaka (0.0 = otwarty, 1.0 = zamkniêty)
    float gripAmount = 0.0f;

    // Obiekt chwytaka – zorientowany na podstawie koñcowego segmentu
    Gripper gripper;

    // Segmenty ramienia i przegubów – logiczna reprezentacja geometrii
    Segment segment1;
    Segment joint1Segment;
    Segment segment2;
    Segment joint2Segment;
    Segment segment3;

    // Konstruktor – inicjalizuje segmenty, przeguby i chwytak
    RobotArm();

    // Rysuje ca³e ramiê wraz z chwytakiem
    void RobotArm::draw(const glm::mat4& projection, const glm::mat4& view,
        const ShaderProgram& shader, Renderer& renderer, Camera& camera);

    // Zwraca pozycjê koñcówki ostatniego segmentu
    glm::vec3 getSegment3Center() const;

    // Zwraca aktualn¹ pozycjê chwytaka w przestrzeni œwiata
    glm::vec3 getGripperPos() const;

    // (Deklaracja) Transformacja koñcówki ramienia — niezaimplementowana tutaj
    glm::mat4 getEndEffectorTransform() const;

private:
    // Rysuje pojedynczy segment z danym kolorem
    void RobotArm::drawSegment(const Segment& s, const glm::mat4& proj, const glm::mat4& view,
        const ShaderProgram& shader, Renderer& renderer, Camera& camera, const glm::vec4& color);
};
