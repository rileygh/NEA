#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glfw/glfw3.h>
#include <iostream>

#include "vec3f.h"
#include "matrix44f.h"
#include "engine.h"
#include "scene.h"
#include "handler.h"

#define WIDTH 960
#define HEIGHT 540

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW error: " << error << ": " << description << '\n';
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) { return 1; }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "test", nullptr, nullptr);

    if (window == nullptr) { return 1; }

    glfwMakeContextCurrent(window); // focus

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460"); // OpenGL v4.6

    Scene scene;
    Sphere s(5, Vec3f(0, 0, -10), Vec3f(255, 0, 0), scene);
    
    Engine engine;
    engine.set_width(WIDTH);
    engine.set_height(HEIGHT);
    engine.allocate_image_buffer();
    engine.set_scene(scene);
    engine.set_defaults();

    Handler handler(window, engine);

    bool cursor_enabled = false;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // listening for events eg. inputs

        handler.update_camera_pos();
        handler.update_camera_dir();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            if (cursor_enabled) { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
            else { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
            cursor_enabled = !cursor_enabled;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Settings");

        float fov = engine.get_fov();
        if (ImGui::SliderFloat("FOV", &fov, 90, 160)) {
            engine.set_fov(fov);
        }

        ImGui::End();

        ImGui::Render();

        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0.45, 0.55, 0.65, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        GLubyte* image_buffer = engine.get_render_data();
        glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, image_buffer);

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
