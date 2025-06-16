#include "ShaderProgram.h"
#include "Renderer.h"
#include "Camera.h"
#include "Segment.h"
#include "Gripper.h"
#include "RobotArm.h"
#include "BoxObject.h"
#include "Recorder.h"
#include "IKController.h"
#include "GuiManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "Simulation.h"


int main() {
    Simulation app;
    app.run();
    return 0;
}