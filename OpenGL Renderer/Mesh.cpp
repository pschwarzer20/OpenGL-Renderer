
#include "Include.h";
#include "Mesh.h";
#include <iostream>

void Mesh::Create(float vertices[], unsigned int indices[], int vertCount, int indCount) {
    verticesCount = vertCount;
    indicesCount = indCount;

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesCount, vertices, GL_STATIC_DRAW);

    // Generate and bind EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount, indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh::Draw() {
    // Bind VAO before drawing
    glBindVertexArray(VAO);

    // Draw mesh
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);

    // Unbind VAO after drawing
    glBindVertexArray(0);
}
