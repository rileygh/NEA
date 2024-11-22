#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glfw/glfw3.h>

#include <iostream>

#include "vec3f.h"
#include "matrix44f.h"

#define WIDTH 960
#define HEIGHT 540

int main(int argc, char **argv) {
    if (!glfwInit()) { return 1; }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "test", nullptr, nullptr);

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
        if (ImGui::Button("Test")) {
            Matrix44f test_m(0.718762, 0.615033, -0.324214, 0, -0.393732, 0.744416, 0.539277, 0, 0.573024, -0.259959, 0.777216, 0, 0.526967, 1.254234, -2.53215, 1);
            Vec3f test_local(-0.5, 0.5, -0.5);
            Vec3f test_world = test_local.mult_with_matrix44f(test_m);
            std::cerr << test_world << '\n';
            // should return -0.315792, 1.4489, -2.48901
            Matrix44f test_m_inverse = test_m.inverse();
            Vec3f test_local_reverse = test_world.mult_with_matrix44f(test_m_inverse);
            std::cerr << test_local_reverse << '\n';
            // should return -0.5, 0.5, -0.5
        }

        if (ImGui::Button("Test 2")) {
            Matrix44f test_m(1, 2, 3, 5, 2, 9, 5, 1, 2, 6, 5, 1, 3, 1, 3, 1);
            Matrix44f test_m_inverse = test_m.inverse();
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    std::cerr << test_m_inverse[i][j];
                }
                std::cerr << '\n';
            }
        }

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
