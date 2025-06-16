#pragma once
#include <glad/glad.h>
#include <string>

// Klasa odpowiadaj¹ca za ³adowanie, kompilacjê i u¿ywanie shaderów OpenGL
class ShaderProgram {
public:
    GLuint id; // Identyfikator programu shaderowego

    // Konstruktor – ³aduje vertex + fragment shader z plików
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    
    // Aktywuje program shaderowy
    void use() const;

    // Zwraca lokalizacjê zmiennej uniform (do ustawiania wartoœci z CPU)
    GLuint uniform(const char* name) const;

private:
    // £aduje kod Ÿród³owy shadera z pliku
    std::string loadShaderSource(const char* filepath);

    // Kompiluje shader (vertex lub fragment) z kodu Ÿród³owego
    GLuint compileShader(GLenum type, const char* source);
};
