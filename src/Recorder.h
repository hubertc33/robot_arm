#pragma once
#include <vector>

// Klasa s³u¿¹ca do nagrywania i odtwarzania ruchów robota
class Recorder {
public:
    bool isRecording = false;   // Czy aktualnie trwa nagrywanie
    bool isPlaying = false;     // Czy aktualnie trwa odtwarzanie
    float timer = 0.0f;         // Zegar wewnêtrzny (czas trwania sesji)
    size_t playIndex = 0;       // Indeks bie¿¹cej klatki odtwarzania

    // Dane nagrane z ka¿dej klatki :
    std::vector<float> recordedJ0, recordedJ1, recordedJ2; // K¹ty przegubów
    std::vector<float> recordedGrip;                       // Poziom chwytu
    std::vector<bool> recordedGrabbing;                   // Czy chwytak trzyma³
    std::vector<float> recordedTime;                      // Znaczniki czasowe


    // Funkcje nagrywania
    void startRecording();
    void stopRecording();
    void startPlayback();
    void stopPlayback();
    void clear();

    // Zapisuje bie¿¹cy stan robota
    void updateRecording(float deltaTime, float j0, float j1, float j2, float grip, bool grabbing);
    
    // Odtwarza stany robota
    bool updatePlayback(float deltaTime, float& j0, float& j1, float& j2, float& grip, bool& grabbing);
};
