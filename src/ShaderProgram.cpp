#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Konstruktor – ³aduje i kompiluje shadery z plików
ShaderProgram::ShaderProgram(const char* vertexPath, const char* fragmentPath) {
    // Wczytaj kody Ÿród³owe shaderów z plików
    std::string vertexCode = loadShaderSource(vertexPath);
    std::string fragmentCode = loadShaderSource(fragmentPath);

    // Kompilacja vertex i fragment shaderów
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    // Tworzenie programu shaderowego i linkowanie shaderów
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    // Sprawdzenie b³êdów linkowania
    int success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cerr << "Shader link error: " << infoLog << std::endl;
    }

    // Usuniêcie shaderów Ÿród³owych
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Aktywuje program shaderowy
void ShaderProgram::use() const {
    glUseProgram(id);
}

// Zwraca lokalizacjê zmiennej uniform o danej nazwie
GLuint ShaderProgram::uniform(const char* name) const {
    return glGetUniformLocation(id, name);
}

// £aduje kod Ÿród³owy shadera z pliku tekstowego
std::string ShaderProgram::loadShaderSource(const char* filepath) {
    std::ifstream file(filepath);     // Otwórz plik
    std::stringstream buffer;
    buffer << file.rdbuf();           // Przenieœ zawartoœæ do bufora
    return buffer.str();              // Zwróæ kod jako string
}

// Kompiluje shader (vertex lub fragment) z kodu Ÿród³owego
GLuint ShaderProgram::compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);                // Tworzy pusty shader
    glShaderSource(shader, 1, &source, nullptr);         // £aduje kod Ÿród³owy
    glCompileShader(shader);                             // Kompiluje shader

    // Sprawdzenie b³êdów kompilacji
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "B³¹d kompilacji shadera: " << infoLog << std::endl;
    }

    return shader;
}
