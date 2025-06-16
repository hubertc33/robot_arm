#include "Renderer.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Inicjalizacja siatki walca: VAO, VBO, EBO
void Renderer::initCylinder() {
    std::vector<float> vertices;
    createCylinder(vertices, cylinderIndices);

    glGenVertexArrays(1, &cylVAO);
    glGenBuffers(1, &cylVBO);
    glGenBuffers(1, &cylEBO);

    glBindVertexArray(cylVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cylVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinderIndices.size() * sizeof(unsigned int), cylinderIndices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);           // pozycja
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // normalna
    glEnableVertexAttribArray(1);
}

// Inicjalizacja siatki sześcianu: wierzchołki i indeksy
void Renderer::initCube() {
    float cubeVertices[] = {
        // Pozycja            // Normalna
        -0.6f, -0.6f, -0.6f,   0.0f,  0.0f, -1.0f,
         0.6f, -0.6f, -0.6f,   0.0f,  0.0f, -1.0f,
         0.6f,  0.6f, -0.6f,   0.0f,  0.0f, -1.0f,
        -0.6f,  0.6f, -0.6f,   0.0f,  0.0f, -1.0f,

        -0.6f, -0.6f,  0.6f,   0.0f,  0.0f,  1.0f,
         0.6f, -0.6f,  0.6f,   0.0f,  0.0f,  1.0f,
         0.6f,  0.6f,  0.6f,   0.0f,  0.0f,  1.0f,
        -0.6f,  0.6f,  0.6f,   0.0f,  0.0f,  1.0f,

        -0.6f,  0.6f,  0.6f,  -1.0f,  0.0f,  0.0f,
        -0.6f,  0.6f, -0.6f,  -1.0f,  0.0f,  0.0f,
        -0.6f, -0.6f, -0.6f,  -1.0f,  0.0f,  0.0f,
        -0.6f, -0.6f,  0.6f,  -1.0f,  0.0f,  0.0f,

         0.6f,  0.6f,  0.6f,   1.0f,  0.0f,  0.0f,
         0.6f,  0.6f, -0.6f,   1.0f,  0.0f,  0.0f,
         0.6f, -0.6f, -0.6f,   1.0f,  0.0f,  0.0f,
         0.6f, -0.6f,  0.6f,   1.0f,  0.0f,  0.0f,

        -0.6f, -0.6f, -0.6f,   0.0f, -1.0f,  0.0f,
         0.6f, -0.6f, -0.6f,   0.0f, -1.0f,  0.0f,
         0.6f, -0.6f,  0.6f,   0.0f, -1.0f,  0.0f,
        -0.6f, -0.6f,  0.6f,   0.0f, -1.0f,  0.0f,

        -0.6f,  0.6f, -0.6f,   0.0f,  1.0f,  0.0f,
         0.6f,  0.6f, -0.6f,   0.0f,  1.0f,  0.0f,
         0.6f,  0.6f,  0.6f,   0.0f,  1.0f,  0.0f,
        -0.6f,  0.6f,  0.6f,   0.0f,  1.0f,  0.0f
    };

    unsigned int cubeIndices[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9,10,10,11, 8,
       12,13,14,14,15,12,
       16,17,18,18,19,16,
       20,21,22,22,23,20
    };

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // pozycja
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // normalna
    glEnableVertexAttribArray(1);
}


// Inicjalizacja siatki 3D – tworzy linie w trzech płaszczyznach
void Renderer::initGrid() {
    const int gridSize = 4;
    const float spacing = 5.0f;

    // Linie poziome w płaszczyźnie XZ
    for (int y = 0; y <= gridSize + 1; ++y) {
        for (int z = -gridSize; z <= gridSize; ++z) {
            gridVertices.insert(gridVertices.end(), {
                -gridSize * spacing, y * spacing + 0.5f, z * spacing,
                 gridSize * spacing, y * spacing + 0.5f, z * spacing });
        }
    }

    // Linie pionowe w płaszczyźnie YZ
    for (int x = -gridSize; x <= gridSize; ++x) {
        for (int z = -gridSize; z <= gridSize; ++z) {
            gridVertices.insert(gridVertices.end(), {
                x * spacing, 0.5f, z * spacing,
                x * spacing, (gridSize + 1) * spacing + 0.5f, z * spacing });
        }
    }

    // Linie pionowe w płaszczyźnie XY
    for (int x = -gridSize; x <= gridSize; ++x) {
        for (int y = 0; y <= gridSize + 1; ++y) {
            gridVertices.insert(gridVertices.end(), {
                x * spacing, y * spacing + 0.5f, -gridSize * spacing,
                x * spacing, y * spacing + 0.5f, gridSize * spacing });
        }
    }

    // Utworzenie buforów OpenGL dla siatki
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);
}

// Inicjalizacja powierzchni ziemi
void Renderer::initGround() {
    float groundVertices[] = {
        //     pozycja              //     normalna
        -20.0f, 0.49f, -20.0f,      0.0f, 1.0f, 0.0f,
         20.0f, 0.49f, -20.0f,      0.0f, 1.0f, 0.0f,
         20.0f, 0.49f,  20.0f,      0.0f, 1.0f, 0.0f,

        -20.0f, 0.49f, -20.0f,      0.0f, 1.0f, 0.0f,
         20.0f, 0.49f,  20.0f,      0.0f, 1.0f, 0.0f,
        -20.0f, 0.49f,  20.0f,      0.0f, 1.0f, 0.0f
    };


    glGenVertexArrays(1, &groundVAO);
    glGenBuffers(1, &groundVBO);

    glBindVertexArray(groundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);

    // pozycja (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // normalna (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

// Funkcja pomocnicza — rysowanie obiektu z danym modelem, kolorem i VAO
void Renderer::drawMesh(const glm::mat4& model, const glm::mat4& viewProj, const ShaderProgram& shader,
    GLuint vao, size_t indexCount, const glm::vec4& color, const glm::vec3& cameraPos)
{
    glm::mat4 mvp = viewProj * model;
    glm::mat4 view = glm::mat4(glm::mat3(viewProj)); // lub przekaż osobno matryce view i projection

    glBindVertexArray(vao);

    // Przesyłanie macierzy i parametrów do shaderów
    glUniformMatrix4fv(shader.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(shader.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shader.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));

    glUniform3f(shader.uniform("lightPos"), 20.0f, 20.0f, 20.0f);
    glUniform3fv(shader.uniform("viewPos"), 1, glm::value_ptr(cameraPos));

    glUniform4fv(shader.uniform("color"), 1, glm::value_ptr(color));

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, 0);
}



// Rysuje siatkę 3D — z użyciem linii (GL_LINES)
void Renderer::drawGrid(const ShaderProgram& shader, const glm::mat4& viewProj) {
    glBindVertexArray(gridVAO);
    glUniformMatrix4fv(shader.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(viewProj));
    glUniform4f(shader.uniform("color"), 0.3f, 0.3f, 0.3f, 1.0f);
    glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(gridVertices.size() / 3));

}

// Rysuje powierzchnię ziemi (płaszczyzna)
void Renderer::drawGround(const ShaderProgram& shader, const glm::mat4& viewProj) {
    glBindVertexArray(groundVAO);
    glUniformMatrix4fv(shader.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(viewProj));
    glUniform4f(shader.uniform("color"), 0.2f, 0.6f, 0.9f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
void Renderer::drawPoint(const glm::mat4& model,
    const glm::mat4& viewProj,
    const ShaderProgram& shader,
    GLuint vao,
    size_t indexCount,
    const glm::vec4& color,
    const glm::vec3& cameraPos)
{
    glUseProgram(shader.id);

    // Wyłącz głębię i włącz blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 mvp = viewProj * model;
    glm::mat4 view = glm::mat4(glm::mat3(viewProj));

    glBindVertexArray(vao);

    glUniformMatrix4fv(shader.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
    glUniformMatrix4fv(shader.uniform("model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(shader.uniform("view"), 1, GL_FALSE, glm::value_ptr(view));

    glUniform3f(shader.uniform("lightPos"), 200.0f, 200.0f, 200.0f); // stałe światło
    glUniform3fv(shader.uniform("viewPos"), 1, glm::value_ptr(cameraPos));

    glUniform4fv(shader.uniform("color"), 1, glm::value_ptr(color));
    glUniform1i(shader.uniform("useLighting"), false); // bez oświetlenia

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexCount), GL_UNSIGNED_INT, 0);

    // Przywróć domyślne ustawienia
    glDisable(GL_BLEND);
    
}



// Czyści bufor ekranu kolorem tła
void Renderer::clear(const glm::vec4& color) {
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Generuje geometrię walca (wierzchołki + indeksy)
// Segmenty – liczba boków, height – wysokość, radius – promień
void Renderer::createCylinder(std::vector<float>& vertices, std::vector<unsigned int>& indices, int segments, float height, float radius) {
    // Dolna podstawa
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        vertices.insert(vertices.end(), { x, 0.0f, z, 0.0f, -1.0f, 0.0f });  // normal w dół
    }
    // Górna podstawa
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        vertices.insert(vertices.end(), { x, height, z, 0.0f, 1.0f, 0.0f });  // normal w górę
    }

    // Środek dolnej
    unsigned int centerBottom = static_cast<unsigned int>(vertices.size() / 6);
    vertices.insert(vertices.end(), { 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f });

    // Środek górnej
    unsigned int centerTop = static_cast<unsigned int>(vertices.size() / 6);
    vertices.insert(vertices.end(), { 0.0f, height, 0.0f, 0.0f, 1.0f, 0.0f });

    // Trójkąty dolnej podstawy
    for (unsigned int i = 0; i < segments; ++i) {
        unsigned int next = (i + 1) % segments;
        indices.insert(indices.end(), { centerBottom, i, next });
    }

    // Trójkąty górnej podstawy
    for (unsigned int i = 0; i < segments; ++i) {
        unsigned int next = (i + 1) % segments;
        indices.insert(indices.end(), { centerTop, segments + next, segments + i });
    }

    // Ściany boczne walca (każdy prostokąt = 2 trójkąty)
    // --- ŚCIANY BOCZNE WALCA --- //
    unsigned int sideStart = static_cast<unsigned int>(vertices.size() / 6);  // gdzie zaczynają się boki

    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * M_PI * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glm::vec3 normal = glm::normalize(glm::vec3(x, 0.0f, z));

        // dodajemy 2 wierzchołki – dół i góra
        vertices.insert(vertices.end(), { x, 0.0f, z, normal.x, normal.y, normal.z });       // dół
        vertices.insert(vertices.end(), { x, height, z, normal.x, normal.y, normal.z });     // góra
    }

    // indeksy dla ścian
    for (unsigned int i = 0; i < segments; ++i) {
        unsigned int next = (i + 1) % segments;

        unsigned int i0 = sideStart + i * 2;
        unsigned int i1 = sideStart + i * 2 + 1;
        unsigned int i2 = sideStart + next * 2;
        unsigned int i3 = sideStart + next * 2 + 1;

        indices.insert(indices.end(), { i0, i1, i2 });
        indices.insert(indices.end(), { i2, i1, i3 });
    }

}
