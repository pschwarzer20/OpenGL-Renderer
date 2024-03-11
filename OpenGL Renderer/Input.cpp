
#include "Include.h"
#include "Input.h"
#include "Window.h"

#include <iostream>

bool _keysDown[349];
bool _keysPressed[349];
bool _keysDownLastCheck[349];

void Input::Init() {

}

void Input::Update() {
	GLFWwindow* window = Window::GetWindow();

	// Search through every single key
	for (int i = 0; i < 349; i++)
	{
		if (glfwGetKey(window, i) == GLFW_PRESS) {
			_keysDown[i] = true;
		}
		else {
			_keysDown[i] = false;
		}

		if (_keysDown[i] && !_keysDownLastCheck[i]) {
			_keysPressed[i] = true;
		}
		else {
			_keysPressed[i] = false;
		}

		_keysDownLastCheck[i] = _keysDown[i];
	}
}

bool Input::KeyPressed(int key) {
	return _keysPressed[key];
}

bool Input::KeyDown(int key) {
	return _keysDown[key];
}
