#pragma once

#include <glm/glm.hpp>

// Deklaracje klas u¿ywanych przez Gripper
class ShaderProgram;
class Renderer;
class Camera;

// Klasa reprezentuj¹ca chwytak robota (dwa palce + belka)
class Gripper {
public:
    float* gripAmount; // WskaŸnik na wartoœæ zacisku(0.0 = otwarty, 1.0 = zamkniêty)
    glm::mat4 parentTransform = glm::mat4(1.0f); // Transformacja nadrzêdna (z segmentu ramienia)

    // Konstruktor – przyjmuje wskaŸnik do zmiennej gripAmount
    Gripper(float* gripPtr); 

    // Rysuje chwytak (palce + belka) z u¿yciem podanych shaderów i renderera
    void draw(const glm::mat4& viewProj, const ShaderProgram& shader, Renderer& renderer, const Camera& camera);
    
    // Zwraca pozycjê œrodka chwytaka w przestrzeni œwiata
    glm::vec3 getGripperPosition() const;
};
