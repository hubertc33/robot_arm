#include "RobotArm.h"
#include "Renderer.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Konstruktor – inicjalizuje segmenty i przeguby ramienia robota
RobotArm::RobotArm()
    : gripper(&gripAmount),
    segment1(&joint0, nullptr, nullptr, 0.0f, {}, { 0,1,0 }, {}, { 0.49f,12.0f,0.49f }),
    joint1Segment(&joint0, nullptr, nullptr, 90.0f, { 0,0,1 }, { 0,7.5f,0 }, { 1,0,0 }, { 0.5f,4,0.5f }),
    segment2(&joint0, &joint1, nullptr, 0.0f, {}, { 0,7.5f,0 }, { 0,0.5f,0 }, { 0.49f,12.0f,0.49f }),
    joint2Segment(&joint0, &joint1, nullptr, 90.0f, { 0,0,1 }, { 0,7.5f,0 }, { 1,7,0 }, { 0.5f,4,0.5f }),
    segment3(&joint0, &joint1, &joint2, 0.0f, {}, { 0,7.5f,0 }, { 0,7.5f,0 }, { 0.49f,12.0f,0.49f })
{}

// Rysuje ca³e ramiê robota oraz chwytak
void RobotArm::draw(const glm::mat4& projection, const glm::mat4& view,
    const ShaderProgram& shader, Renderer& renderer, Camera& camera) {
    glm::vec3 camPos = camera.getCameraPosition();
    // Rysuj podstawê (cylinder przy ziemi
    glm::mat4 baseModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f));
    renderer.drawMesh(baseModel, projection * view, shader, renderer.cylVAO, renderer.cylinderIndices.size(), { 1.0f, 0.4f, 0.1f, 1.0f },camPos);

    
    // Rysuj segmenty i przeguby

    drawSegment(segment1, projection, view, shader, renderer,camera, { 1.0f, 1.0f, 1.0f, 1.0f });
    drawSegment(joint1Segment, projection, view, shader, renderer, camera , { 1.0f, 0.4f, 0.1f, 1.0f });
    drawSegment(segment2, projection, view, shader, renderer,  camera , { 1.0f, 1.0f, 1.0f, 1.0f });
    drawSegment(joint2Segment, projection, view, shader, renderer, camera, { 1.0f, 0.4f, 0.1f, 1.0f });
    drawSegment(segment3, projection, view, shader, renderer, camera, { 1.0f, 1.0f, 1.0f, 1.0f });

    // Oblicz transformacjê koñcowego segmentu i narysuj chwytak
    glm::mat4 base = segment3.computeTransform(glm::mat4(1.0f));
    base = glm::translate(base, glm::vec3(0.0f, 0.006f, 0.0f));
    gripper.parentTransform = base;
    gripper.draw(projection * view, shader, renderer, camera);
}

// Zwraca pozycjê koñcówki ostatniego segmentu (centrum chwytaka)
glm::vec3 RobotArm::getSegment3Center() const {
    glm::mat4 model = segment3.computeTransform(glm::mat4(1.0f));
    return glm::vec3(model * glm::vec4(0.0f, 0.7f, 0.0f, 1.0f));
}

// Zwraca globaln¹ pozycjê chwytaka
glm::vec3 RobotArm::getGripperPos() const {
    return gripper.getGripperPosition();
}

// Zwraca pe³n¹ macierz transformacji koñcówki ramienia (ostatniego segmentu)
glm::mat4 RobotArm::getEndEffectorTransform() const {
    return segment3.computeTransform(glm::mat4(1.0f));
}

// Rysuje pojedynczy segment ramienia (lub przegub) z podanym kolorem
void RobotArm::drawSegment(const Segment& s, const glm::mat4& proj, const glm::mat4& view,
    const ShaderProgram& shader, Renderer& renderer, Camera& camera, const glm::vec4& color) {
    glm::vec3 camPos = camera.getCameraPosition();
    renderer.drawMesh(s.computeTransform(glm::mat4(1.0f)), proj * view, shader, renderer.cylVAO, renderer.cylinderIndices.size(), color,camPos);
}
