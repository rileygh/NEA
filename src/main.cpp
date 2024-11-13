// this file does nothing yet

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glfw/glfw3.h>

#include <iostream>

#include "vec3f.h"

#define WIDTH 500
#define HEIGHT 500

int main(int argc, char **argv) {
    GLFWwindow* window = glfwCreateWindow(960, 540, "test", nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }
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
