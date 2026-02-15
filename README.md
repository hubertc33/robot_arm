# 3-DOF Robot Arm Simulator (C++ / OpenGL)

An interactive simulator of a 3-degree-of-freedom robotic arm, developed in C++ using OpenGL.
The project includes a kinematic model, 3D rendering, manual control (GUI + keyboard), a gripper module, and a trajectory recording/playback system.

---

## Preview

![Demo](demo.gif)


---

## Features

- 3 DOF robotic arm simulation + gripper
- Control methods:
  - keyboard
  - graphical GUI (sliders, input fields, buttons)
- Joint angle sliders for each joint
- XYZ position input with automatic arm positioning (Go to point)
- Trajectory recording system:
  - motion recording
  - frame saving
  - path playback
- Interactive 3D camera:
  - rotation
  - zoom in / out
- 3D object rendering (arm, gripper, ground plane, cube)
- Grid display mode
- Clear visualization of arm segments

---

## Controls

### Keyboard

| Key | Function |
|--------|---------|
| Q / E  | Joint 0 – increase / decrease |
| A / D  | Joint 1 – increase / decrease |
| Z / C  | Joint 2 – increase / decrease |
| SPACE  | Close / open gripper |

---

### GUI

- Joint control sliders 
- Value input fields (Target X, Y, Z)  
- Go to point **Idź do punktu**  
- Start recording **Nagrywaj**  
- Stop recording **Zakończ nagrywanie**  
- Play trajectory **Odtwórz trajektorię**  
- Stop playback **Zakończ odtwarzanie**  
- Gripper position display
- Show grid toggle **Pokaż siatkę**  

---

### Camera Controlsą

| Action | Function |
|-------|---------|
| Scroll | Zoom in / out |
| Left mouse button + drag | Rotate view |
| Right mouse button| Pan the scene (if enabled) |

---

## Kinematics

- The project uses a classic kinematic chain model, including:
- translation and rotation transforms
- revolute joints
- end-effector position computation
- target positioning in 3D space (XYZ)
- an initial inverse kinematics implementation (IKController))

---

## Project Structure
```
src/
├── BoxObject.cpp/.h # Cube objects
├── Camera.cpp/.h # 3D camera controls
├── Gripper.cpp/.h # Gripper logic
├── GuiManager.cpp/.h # GUI
├── IKController.cpp/.h # Inverse kinematics / target point
├── InputManager.cpp/.h # Keyboard and mouse input
├── Recorder.cpp/.h # Trajectory recording/playback
├── Renderer.cpp/.h # OpenGL rendering
├── RobotArm.cpp/.h # Robot arm logic
├── Scene.cpp/.h # 3D scene
├── Segment.cpp/.h # Arm segments
├── ShaderProgram.cpp/.h # Shader handling
├── Simulation.cpp/.h # Simulation logic
└── main.cpp # Program entry point
```
---

## Technologies

- C++17  
- OpenGL  
- GLFW / GLUT  
- GLAD / GLEW  
- ImGui  
- 3D math (matrices, vectors, rotations)

