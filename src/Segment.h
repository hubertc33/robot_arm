#pragma once

#include <glm/glm.hpp>

// Klasa reprezentuj¹ca pojedynczy segment ramienia robota
class Segment {
public:
    // WskaŸniki na k¹ty obrotu przypisanych przegubów
    float* joint0Angle;
    float* joint1Angle;
    float* joint2Angle;

    // Sta³y obrót (k¹t w stopniach) i oœ, wokó³ której nastêpuje
    float fixedAngle;
    glm::vec3 fixedAxis;

    // Przesuniêcie wzglêdem poprzedniego segmentu
    glm::vec3 baseTranslation;
    
    // Lokalny offset – wewnêtrzne przesuniêcie w segmencie
    glm::vec3 offset;
    
    // Wektor skalowania – np. d³ugoœæ lub gruboœæ segmentu
    glm::vec3 scale;

    // Konstruktor – przypisuje wartoœci i wskaŸniki
    Segment(float* j0, float* j1, float* j2,
        float fixedAngleDeg, glm::vec3 fixedAxis,
        glm::vec3 baseTrans, glm::vec3 localOffset, glm::vec3 scl);

    // Oblicza pe³n¹ transformacjê macierzy segmentu wzglêdem rodzica
    glm::mat4 computeTransform(const glm::mat4& parent) const;
};
