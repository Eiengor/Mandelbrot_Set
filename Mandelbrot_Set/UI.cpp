#include "UI.h"


UI::UI(Application& app, int fontGlobalScale)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 1.5f;
    ImGui::StyleColorsClassic(); // You can use Classic(), Light(), etc.

    // Initialize ImGui with GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(app.getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void UI::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UI::ShowWindow(float zoom, float center_x, float center_y, Performance& performance)
{
    ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_Once);
    ImGui::Begin("Mandelbrot Controls");
    ImGui::Text("Zoom: %.3f", zoom * 100);
    ImGui::Text("Center X: %.5f", center_x);
    ImGui::Text("Center Y: %.5f", center_y);
    ImGui::Text("FPS: %.1f", performance.getAverageFPS());
    ImGui::End();
}

void UI::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::clear()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
