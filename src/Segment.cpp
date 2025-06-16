#include "Segment.h"
#include <glm/gtc/matrix_transform.hpp>

// Konstruktor — przypisuje wskaŸniki na k¹ty przegubów i ustala geometriê segmentu
Segment::Segment(float* j0, float* j1, float* j2,
    float fixedAngleDeg, glm::vec3 fixedAxis,
    glm::vec3 baseTrans, glm::vec3 localOffset, glm::vec3 scl)
    : joint0Angle(j0), joint1Angle(j1), joint2Angle(j2),
    fixedAngle(fixedAngleDeg), fixedAxis(fixedAxis),
    baseTranslation(baseTrans), offset(localOffset), scale(scl) {}

// Oblicza globaln¹ macierz transformacji segmentu na podstawie przegubów i parametrów lokalnych
glm::mat4 Segment::computeTransform(const glm::mat4& parent) const {
    glm::mat4 model = parent;

    // Obrót wokó³ joint0 (oœ Y) 
    if (joint0Angle)
        model = glm::rotate(model, glm::radians(*joint0Angle), glm::vec3(0, 1, 0));

    // Translacja podstawowa – przesuniêcie segmentu od poprzednika
    model = glm::translate(model, baseTranslation);

    // Obrót wokó³ joint1 (oœ X) jeœli aktywny
    if (joint1Angle)
        model = glm::rotate(model, glm::radians(*joint1Angle), glm::vec3(1, 0, 0));

    // Lokalny offset – np. punkt obrotu dla joint2
    model = glm::translate(model, offset);

    // Joint2 (oœ X) – obrót wzglêdem œrodka segmentu
    if (joint2Angle) {
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(*joint2Angle), glm::vec3(1, 0, 0));
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    }

    // Sta³y obrót o 90 stopni dla przegubów
    if (fixedAngle != 0.0f)
        model = glm::rotate(model, glm::radians(fixedAngle), fixedAxis);

    // Skalowanie geometrii (np. d³ugoœæ/wysokoœæ segmentu)
    model = glm::scale(model, scale);
    return model;
}
