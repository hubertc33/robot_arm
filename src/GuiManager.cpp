#include "GuiManager.h"
#include "RobotArm.h"
#include "IKController.h"
#include "Recorder.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


// Inicjalizacja biblioteki ImGui
void GuiManager::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

// Zamyka i sprz¹ta po ImGui
void GuiManager::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

// Rozpoczyna now¹ klatkê GUI
void GuiManager::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

// Koñczy klatkê GUI i rysuje interfejs
void GuiManager::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Tworzy okno GUI do sterowania ramieniem i systemem IK
void GuiManager::draw(RobotArm& robot, IKController& ik, Recorder& recorder,
    const glm::vec3& gripperPos, bool& showGrid)
{
    ImGui::SetNextWindowSize(ImVec2(300, 250), ImGuiCond_FirstUseEver);
    ImGui::Begin("Sterowanie Ramieniem");

    // Suwaki do sterowania przegubami (manualnie)
    float tempJ0 = robot.joint0;
    if (ImGui::SliderFloat("Joint 0", &tempJ0, -180.0f, 180.0f)) {
        ik.cancel();
        robot.joint0 = tempJ0;
    }

    // Dynamiczny zakres ograniczaj¹cy ruch drugiego przegubu
    float dynamicLimit = 135.0f - 0.333f * std::abs(robot.joint2);
    float tempJ1 = robot.joint1;
    if (ImGui::SliderFloat("Joint 1", &tempJ1, -dynamicLimit, dynamicLimit)) {
        ik.cancel();
        float backup = robot.joint1;
        robot.joint1 = tempJ1;
        if (robot.getSegment3Center().y - 0.7f < 0.5f)
            robot.joint1 = backup;
    }

    float tempJ2 = robot.joint2;
    if (ImGui::SliderFloat("Joint 2", &tempJ2, -135.0f, 135.0f)) {
        ik.cancel();
        float backup = robot.joint2;
        robot.joint2 = tempJ2;
        if (robot.getSegment3Center().y - 0.7f < 0.5f)
            robot.joint2 = backup;
    }

    // Wprowadzanie wspó³rzêdnych celu dla IK
    ImGui::InputFloat("Target X", &ik.targetX);
    ImGui::InputFloat("Target Y", &ik.targetY);
    ImGui::InputFloat("Target Z", &ik.targetZ);

    // Rozpocznij interpolacjê jeœli uda siê rozwi¹zaæ IK
    if (ImGui::Button("Idz do punktu")) {
        float j0, j1, j2;
        if (ik.solveIK(glm::vec3(ik.targetX, ik.targetY, ik.targetZ), j0, j1, j2)) {
            ik.startInterpolation(j0, j1, j2);
        }
    }

    // Uaktualnij interpolacjê w czasie
    ik.updateInterpolation(robot.joint0, robot.joint1, robot.joint2, ImGui::GetIO().DeltaTime);

    // Kontrola nagrywania ruchów
    if (ImGui::Button("Nagrywaj")) recorder.startRecording();
    if (ImGui::Button("Zakoncz nagrywanie")) recorder.stopRecording();
    if (ImGui::Button("Odtworz")) {
        ik.cancel();
        recorder.startPlayback();
    }
    if (ImGui::Button("Zakoncz odtwarzanie")) recorder.stopPlayback();

    // Informacja o stanie
    if (recorder.isRecording)
        ImGui::TextColored(ImVec4(0.1f, 1.0f, 0.1f, 1.0f), "Nagrywanie");
    else if (recorder.isPlaying)
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.1f, 1.0f), "Odtwarzanie");

    // Pozycja chwytaka
    ImGui::Separator();
    ImGui::Text("Gripper Position:");
    ImGui::Text("X: %.2f", gripperPos.x);
    ImGui::Text("Y: %.2f", gripperPos.y);
    ImGui::Text("Z: %.2f", gripperPos.z);

    // Prze³¹cznik widocznoœci siatki
    ImGui::Checkbox("Pokaz siatke", &showGrid);
    ImGui::End();
}
