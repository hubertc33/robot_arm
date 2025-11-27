# 3-DOF Robot Arm Simulator (C++ / OpenGL)

Interaktywny symulator 3-stopniowego ramienia robota opracowany w języku C++ z wykorzystaniem OpenGL.  
Projekt zawiera model kinematyczny, rendering 3D, sterowanie manualne (GUI + klawiatura), moduł chwytaka oraz system nagrywania i odtwarzania trajektorii.

---

## Podgląd działania

![Demo](assets/demo.gif)

### Zrzut ekranu
![Screenshot](assets/screenshot.png)

---

## Funkcjonalności

- Symulacja ramienia robota (3 DOF) + chwytak  
- Sterowanie:
  - klawiatura
  - graficzny interfejs GUI (suwaki, pola, przyciski)
- Suwaki regulacji dla każdego przegubu
- Wprowadzanie pozycji XYZ i automatyczne ustawianie ramienia (Go to point)
- System nagrywania trajektorii:
  - nagrywanie ruchu
  - zapis klatek
  - odtwarzanie ścieżki
- Interaktywna kamera 3D:
  - obracanie
  - przybliżanie / oddalanie
- Renderowanie obiektów 3D (ramię, chwytak, podłoże, kostka)
- Tryb wyświetlania siatki
- Czytelna wizualizacja segmentów

---

## Sterowanie

### Klawiatura

| Klawisz | Funkcja |
|--------|---------|
| Q / E  | Joint 0 – zwiększ / zmniejsz |
| A / D  | Joint 1 – zwiększ / zmniejsz |
| Z / C  | Joint 2 – zwiększ / zmniejsz |
| SPACE  | Zamknięcie / otwarcie chwytaka |

---

### GUI

- Suwaki regulacji każdego przegubu  
- Pola wartości (Target X, Y, Z)  
- **Idź do punktu**  
- **Nagrywaj**  
- **Zakończ nagrywanie**  
- **Odtwórz trajektorię**  
- **Zakończ odtwarzanie**  
- Wyświetlanie pozycji chwytaka  
- Przełącznik **Pokaż siatkę**  

---

### Sterowanie kamerą

| Akcja | Funkcja |
|-------|---------|
| Scroll | Przybliżenie / oddalenie |
| Lewy przycisk + ruch | Obracanie widoku |
| Prawy przycisk | Przesuwanie sceny (jeśli włączone) |

---

## Kinematyka

Projekt wykorzystuje klasyczny model łańcucha kinematycznego, obejmujący:

- transformacje translacji i rotacji
- przeguby obrotowe
- obliczanie pozycji efektora
- ustalanie pozycji docelowej w przestrzeni (XYZ)
- wstępną implementację kinematyki odwrotnej (IKController)

---

## Struktura projektu
src/
├── BoxObject.cpp/.h # Obiekty kostek
├── Camera.cpp/.h # Kontrola kamery 3D
├── Gripper.cpp/.h # Logika chwytaka
├── GuiManager.cpp/.h # GUI
├── IKController.cpp/.h # Kinematyka odwrotna / target point
├── InputManager.cpp/.h # Klawiatura i mysz
├── Recorder.cpp/.h # Nagrywanie/odtwarzanie trajektorii
├── Renderer.cpp/.h # Rendering OpenGL
├── RobotArm.cpp/.h # Logika ramienia
├── Scene.cpp/.h # Scena 3D
├── Segment.cpp/.h # Segmenty ramienia
├── ShaderProgram.cpp/.h # Obsługa shaderów
├── Simulation.cpp/.h # Logika symulacji
└── main.cpp # Punkt wejściowy programu

---

## Technologie

- C++17  
- OpenGL  
- GLFW / GLUT  
- GLAD / GLEW  
- ImGui  
- Matematyka 3D (macierze, wektory, rotacje)

