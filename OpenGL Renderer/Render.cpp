
#include "Include.h"
#include "Render.h"
#include "Shader.h"
#include "Mesh.h"

#include <iostream>

float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

Shader shader;
Mesh triangle;

void Render::Init() {
    shader.Load("vertexTest", "fragmentTest");
    triangle.Create(vertices, indices);
}

void Render::Update() {
    // Set the background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
    shader.SetVec4("ourColor", glm::vec4(1.0f, greenValue, 0.2f, 1.0f));

    triangle.Draw();
}