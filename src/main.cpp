// this file does nothing yet

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glfw/glfw3.h>

#include <iostream>

#include "vec3f.h"

#define WIDTH 960
#define HEIGHT 540

int main(int argc, char **argv) {
    float temp_fov = 0.0;

    if (!glfwInit()) { return 1; }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "test", nullptr, nullptr);
    if (window == nullptr) { return 1; }

    if (!glfwInit()) { return 1; }
    GLFWwindow* window = glfwCreateWindow(1280, 720, "test", nullptr, nullptr);
    
    if (window == nullptr) { return 1; }
    glfwMakeContextCurrent(window); // focus

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460"); // OpenGL v4.6

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // listening for events eg. inputs

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");
        ImGui::Text("some placeholder text...");
        ImGui::SliderFloat("FOV", &temp_fov, 90.0, 160.0); // test, won't keep this var
        ImGui::End();

        ImGui::Begin("Scene");
        ImGui::End();

        ImGui::Render();

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.45, 0.55, 0.65, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // destroy frame & context
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
