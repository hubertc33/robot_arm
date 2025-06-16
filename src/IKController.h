#pragma once
#include <glm/glm.hpp>

class IKController {
public:
    // Docelowe k¹ty przegubów (wynik rozwi¹zania IK)
    float targetJ0 = 0.0f;
    float targetJ1 = 0.0f;
    float targetJ2 = 0.0f;

    // Wspó³rzêdne celu w przestrzeni 3D
    float targetX = 0.0f;
    float targetY = 0.0f;
    float targetZ = 0.0f;

    // Status interpolacji
    bool isInterpolating = false;
    float time = 0.0f;        // Bie¿¹cy czas trwania interpolacji
    float duration = 8.0f;    // Ca³kowity czas interpolacji

    // Rozpoczêcie interpolacji do zadanych k¹tów
    void startInterpolation(float j0, float j1, float j2);
    
    // Przerwanie interpolacji
    void cancel();
    
    // Aktualizacja interpolacji na podstawie deltaTime
    bool updateInterpolation(float& j0, float& j1, float& j2, float deltaTime);
    
    // Rozwi¹zuje IK — zwraca true jeœli uda siê wyznaczyæ k¹ty do wskazanego punktu
    bool solveIK(const glm::vec3& target, float& j0, float& j1, float& j2);
};
