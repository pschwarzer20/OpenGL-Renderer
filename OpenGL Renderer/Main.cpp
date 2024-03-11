
#include "Include.h"
#include "Window.h"
#include "Render.h"
#include "Input.h"

#include <iostream>

int main(void)
{
    int width = 800;
    int height = 600;
    const char* title = "OpenGL Renderer";

    Window::Init(width, height, title);
    Render::Init();
    GLFWwindow* window = Window::GetWindow();

    while (!glfwWindowShouldClose(window))
    {
        Window::Render();
        Render::Update();
        Input::Update();

        if (Input::KeyPressed(GLFW_KEY_ESCAPE)) {
            return -1;
        }

        if (Input::KeyPressed(GLFW_KEY_ENTER)) {
            Window::ToggleFullscreen();
        }
    }
    
    return 0;
}