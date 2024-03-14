#pragma once

class Mesh {
public:
	void Create(float vertices[], unsigned int indices[], int vertCount, int indicesCount);
	void Draw();

private:
	unsigned int VBO, VAO, EBO;
	int verticesCount, indicesCount;
};