#pragma once

namespace Window
{
	void Init(int width, int height, const char* title);
	void Render();
	GLFWwindow* GetWindow();
	void ToggleFullscreen();
}
