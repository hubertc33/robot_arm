#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class ShaderProgram;
class Camera;


// Klasa odpowiedzialna za inicjalizacjê i rysowanie obiektów 3D: siatki, walca, szeœcianu, pod³o¿a
class Renderer {
public:
    // Bufory i VAO dla ró¿nych obiektów
    GLuint cylVAO, cylVBO, cylEBO;     // Walec
    GLuint gridVAO, gridVBO;           // Siatka
    GLuint cubeVAO, cubeVBO, cubeEBO;  // Szeœcian
    GLuint groundVAO, groundVBO;       // Ziemia


    std::vector<unsigned int> cylinderIndices; // Indeksy dla walca
    std::vector<float> gridVertices;           // Wierzcho³ki siatki 3D

    // Inicjalizacja geometrii
    void initCylinder();
    void initCube();
    void initGrid();
    void initGround();

    // Rysuje obiekt (mesh) z danym kolorem, VAO i modelem
    void drawMesh(const glm::mat4& model, const glm::mat4& viewProj,
        const ShaderProgram& shader, GLuint vao, size_t indexCount,
        const glm::vec4& color, const glm::vec3& cameraPos);

    // Rysuje ca³¹ siatkê 3D
    void drawGrid(const ShaderProgram& shader, const glm::mat4& viewProj);
    
    // Rysuje ziemiê (p³aska powierzchnia)
    void drawGround(const ShaderProgram& shader, const glm::mat4& viewProj);

    void Renderer::drawPoint(const glm::mat4& model,
        const glm::mat4& viewProj,
        const ShaderProgram& shader,
        GLuint vao,
        size_t indexCount,
        const glm::vec4& color,
        const glm::vec3& cameraPos);

    // Czyœci ekran i bufor g³êbokoœci
    void clear(const glm::vec4& color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

private:
    // Tworzy dane geometrii walca
    void createCylinder(std::vector<float>& vertices, std::vector<unsigned int>& indices,
        int segments = 32, float height = 0.5f, float radius = 2.0f);
};
