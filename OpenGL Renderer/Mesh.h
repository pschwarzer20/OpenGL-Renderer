#pragma once

class Mesh {
public:
	void Create(float vertices[], unsigned int indices[]);
	void Draw();

private:
	unsigned int VBO, VAO, EBO;
	float* vertices;
	unsigned int* indices;
	unsigned int verticesCount, indicesCount;
};