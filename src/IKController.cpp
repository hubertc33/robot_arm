#include "IKController.h"
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

// Rozpoczêcie interpolacji do zadanych k¹tów przegubów
void IKController::startInterpolation(float j0, float j1, float j2) {
    targetJ0 = j0;
    targetJ1 = j1;
    targetJ2 = j2;
    time = 0.0f;
    isInterpolating = true;
}

// Anulowanie bie¿¹cej interpolacji
void IKController::cancel() {
    isInterpolating = false;
}

// Aktualizuje bie¿¹ce k¹ty przegubów, interpoluj¹c je w czasie
bool IKController::updateInterpolation(float& j0, float& j1, float& j2, float deltaTime) {
    if (!isInterpolating) return false;

    time += deltaTime;
    float t = glm::clamp(time / duration, 0.0f, 1.0f); // Normalizacja czasu do przedzia³u 0–1

    // Funkcja pomocnicza – interpolacja przez najkrótsz¹ drogê (obrót)
    auto shortestAngle = [](float from, float to) {
        float diff = fmod((to - from + 540.0f), 360.0f) - 180.0f;
        return from + diff;
        };

    // Interpolacja k¹ta obrotu dla ka¿dego przegubu
    j0 = glm::mix(j0, shortestAngle(j0, targetJ0), t);
    j1 = glm::mix(j1, targetJ1, t);
    j2 = glm::mix(j2, targetJ2, t);

    // Jeœli interpolacja siê zakoñczy³a — ustaw koñcowe wartoœci
    if (t >= 1.0f) {
        j0 = targetJ0;
        j1 = targetJ1;
        j2 = targetJ2;
        isInterpolating = false;
    }

    return true;
}

bool IKController::solveIK(const glm::vec3& target, float& j0, float& j1, float& j2) {
    constexpr float L1 = 7.0f;
    constexpr float L2 = 7.0f;
    constexpr float L3 = 7.8f;

    j0 = glm::degrees(atan2(target.x, target.z));
    float dz = sqrt(target.x * target.x + target.z * target.z);
    float dy = target.y - 7.5f;

    float dist = sqrt(dy * dy + dz * dz);
    if (dist > L2 + L3 || dist < fabs(L2 - L3)) return false;
    if (target.y < 4.0f) return false;

    float angleElbow = acos(glm::clamp((L2 * L2 + L3 * L3 - dist * dist) / (2 * L2 * L3), -1.0f, 1.0f));
    j2 = glm::degrees(glm::pi<float>() - angleElbow);

    float angleToTarget = atan2(dz, dy);
    float angleA = acos(glm::clamp((L2 * L2 + dist * dist - L3 * L3) / (2 * L2 * dist), -1.0f, 1.0f));
    j1 = glm::degrees(angleToTarget - angleA);

    return true;
}
