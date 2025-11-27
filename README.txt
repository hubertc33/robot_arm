3-DOF Robot Arm Simulator (C++ / OpenGL)

Interaktywny symulator 3-stopniowego ramienia robota opracowany w języku C++ z wykorzystaniem OpenGL.
Projekt zawiera kompletny model kinematyczny, system renderowania 3D, sterowanie manualne (klawiatura + GUI), obsługę chwytaka oraz moduł zapisu i odtwarzania trajektorii ruchu.

Podgląd działania
<!-- GIF można podpiąć tutaj -->

[Wstaw GIF tutaj]

Zrzut ekranu

Funkcjonalności

Symulacja ruchu ramienia robota (3 DOF) z osobnym modułem chwytaka

Sterowanie ręczne poprzez:

klawiaturę

interfejs GUI (suwaki, pola wpisywania wartości, przyciski akcji)

Suwaki regulacji kąta każdego przegubu (Joint 0–2)

Wprowadzanie pozycji XYZ i automatyczne ustawianie ramienia (Go to point)

Rejestrowanie trajektorii ruchu:

nagrywanie

zapis klatek ruchu

odtwarzanie zarejestrowanej ścieżki

Interaktywna kamera 3D (obracanie, zoom, przesuwanie)

Renderowanie obiektów:

podłoże

elementy ramienia

chwytak

kostki / obiekty manipulacyjne

Czytelna wizualizacja — segmenty kolorystyczne i przejrzysta prezentacja przestrzenna

Tryb wyświetlania siatki (opcjonalnie)

Sterowanie
Klawiatura
Klawisz	Funkcja
Q / E	Joint 0: zwiększ / zmniejsz
A / D	Joint 1: zwiększ / zmniejsz
Z / C	Joint 2: zwiększ / zmniejsz
SPACE	Zamknięcie / otwarcie chwytaka
GUI

Suwaki regulacji przegubów

Pola wprowadzania pozycji (Target X, Y, Z)

Przycisk Idź do punktu

Przycisk Nagrywaj

Przycisk Zakończ nagrywanie

Przycisk Odtwórz trajektorię

Przycisk Zakończ odtwarzanie

Wyświetlanie pozycji chwytaka

Przełącznik Pokaż siatkę

Sterowanie kamerą
Akcja	Funkcja
Scroll	Przybliżenie / oddalenie
Lewy przycisk myszy + ruch	Obracanie kamery
Prawy przycisk myszy (opcjonalnie)	Przesuwanie sceny
Kinematyka

Projekt wykorzystuje klasyczny model łańcucha kinematycznego, obejmujący:

Transformacje rotacji oraz translacji

Połączenia przegubowe (revolute joints)

Obliczanie pozycji efektora

Ustalanie pozycji docelowej poprzez podanie wartości XYZ

Wstępną implementację kinematyki odwrotnej (IKController)

Struktura projektu
src/
├── BoxObject.cpp/.h        # Obiekty kostek
├── Camera.cpp/.h           # Kontrola kamery 3D
├── Gripper.cpp/.h          # Logika chwytaka
├── GuiManager.cpp/.h       # Warstwa interfejsu użytkownika
├── IKController.cpp/.h     # Kinematyka odwrotna / punkt docelowy
├── InputManager.cpp/.h     # Obsługa klawiatury i myszy
├── Recorder.cpp/.h         # Nagrywanie i odtwarzanie trajektorii
├── Renderer.cpp/.h         # Rendering OpenGL
├── RobotArm.cpp/.h         # Logika ramienia i przegubów
├── Scene.cpp/.h            # Scena (obiekty, podłoże)
├── Segment.cpp/.h          # Segmenty ramienia
├── ShaderProgram.cpp/.h    # Obsługa shaderów
├── Simulation.cpp/.h       # Główna logika symulacji
└── main.cpp                # Punkt wejściowy programu

Środowisko i technologie

C++ 17

OpenGL

GLFW / GLUT (w zależności od konfiguracji)

GLEW / GLAD (loader funkcji)

ImGui – interfejs GUI

Matematyka 3D: macierze transformacji, wektory, rotacje
