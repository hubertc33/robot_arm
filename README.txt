# 3-DOF Robot Arm Simulator (C++ / OpenGL)

![Demo](img/demo.gif)

## 📸 Screenshot
![Screenshot](img/preview.png)

---

## 🚀 Funkcje
- **3 DOF + chwytak**
- Sterowanie z klawiatury
- Fizyczne suwaki w GUI
- Wpisywanie punktu XYZ i automatyczne przejście
- Nagrywanie i odtwarzanie trajektorii
- Interaktywna kamera 3D (scroll + obrót)
- Wyświetlanie pozycji efektora

---

## 🎮 Sterowanie

### Klawiatura
| Klawisz | Funkcja |
|--------|----------|
| Q / E | Joint 0 |
| A / D | Joint 1 |
| Z / C | Joint 2 |
| SPACE | Chwytak |

### Mysz
| Akcja | Funkcja |
|--------|----------|
| Scroll | Zoom |
| LPM + ruch | Obrót kamery |

---

## 🛠️ Kompilacja (CMake)

```bash
mkdir build
cd build
cmake ..
make
./RobotArm
