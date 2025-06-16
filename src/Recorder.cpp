#include "Recorder.h"
#include <iostream>

// Rozpoczyna nagrywanie 
void Recorder::startRecording() {
    clear();              // Usuniêcie starych danych
    isRecording = true;   // Aktywacja trybu nagrywania
    timer = 0.0f;         // Reset czasu nagrywania
}

// Zatrzymuje nagrywanie
void Recorder::stopRecording() {
    isRecording = false;
}

// Rozpoczyna odtwarzanie
void Recorder::startPlayback() {
    if (!recordedTime.empty()) {
        isPlaying = true;
        timer = 0.0f;
        playIndex = 0;
    }
}

// Zatrzymuje odtwarzanie
void Recorder::stopPlayback() {
    isPlaying = false;
}

// Czyœci wszystkie dane nagrania
void Recorder::clear() {
    recordedJ0.clear();
    recordedJ1.clear();
    recordedJ2.clear();
    recordedGrip.clear();
    recordedGrabbing.clear();
    recordedTime.clear();
}

// Aktualizuje dane nagrania — zapisuje co 0.05 sekundy
void Recorder::updateRecording(float deltaTime, float j0, float j1, float j2, float grip, bool grabbing) {
    timer += deltaTime;
    if (recordedTime.empty() || timer - recordedTime.back() > 0.05f) {
        recordedTime.push_back(timer);
        recordedJ0.push_back(j0);
        recordedJ1.push_back(j1);
        recordedJ2.push_back(j2);
        recordedGrip.push_back(grip);
        recordedGrabbing.push_back(grabbing);
    }
}

// Odtwarza dane z nagrania - przekazuje do aktualnego stanu
bool Recorder::updatePlayback(float deltaTime, float& j0, float& j1, float& j2, float& grip, bool& grabbing) {
    if (!isPlaying || playIndex >= recordedTime.size()) return false;

    timer += deltaTime;
    if (timer >= recordedTime[playIndex]) {
        j0 = recordedJ0[playIndex];
        j1 = recordedJ1[playIndex];
        j2 = recordedJ2[playIndex];
        grip = recordedGrip[playIndex];
        grabbing = recordedGrabbing[playIndex];
        playIndex++;

    }

    if (playIndex >= recordedTime.size()) {
        isPlaying = false;
    }

    return isPlaying;
}
