
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
unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

float vertices2[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};
unsigned int indices2[] = {
    0, 1, 3,   // first triangle
};

Shader shader;
Mesh box;
Mesh triangle;

bool _wireframe = false; // TODO: Make Renderer a class so it can contain variables like this

void Render::Init() {
    shader.Load("vertexTest", "fragmentTest");
    box.Create(vertices, indices, sizeof(vertices), sizeof(indices));
    triangle.Create(vertices2, indices2, sizeof(vertices2), sizeof(indices2));
}

void Render::Update() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader.Use();
    shader.SetVec4("ourColor", glm::vec4(1.0f, 1.0f, 0.2f, 1.0f));
    box.Draw();

    float greenValue = (sin(glfwGetTime()) / 2.0f) + 0.5f;
    shader.SetVec4("ourColor", glm::vec4(1.0f, greenValue, 0.2f, 1.0f));
    triangle.Draw();
}

void Render::ToggleWireframe() {
    _wireframe = !_wireframe;
    if (_wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
