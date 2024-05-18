
#include "Include.h"
#include "Window.h"

#include <iostream>

struct screenSize {
	public : int width;
	public : int height;
};

class OPGLRWindow {
public:
	// Windowed
	bool GetWindowed() {
		return windowed;
	}
	void SetWindowed(bool state) {
		this->windowed = state;
	}
	void ToggleWindowed() {
		this->windowed = !this->windowed;
	}
	// Screen Dimensions
	void SetMinimizedWindowSize(int width, int height) {
		windowDimensions.width = width;
		windowDimensions.height = height;
	}
	screenSize GetMinimizedWindowsSize() {
		return windowDimensions;
	}
	void SetFullscreenSize(int width, int height) {
		fullscreenDimensions.width = width;
		fullscreenDimensions.height = height;
	}
	screenSize GetFullscreenSize() {
		return fullscreenDimensions;
	}
	int lastPosX = 0;
	int lastPosY = 0;
private:
	bool windowed = true;
	screenSize windowDimensions;
	screenSize fullscreenDimensions;
};

namespace Window {
	int _currentWidth = 0;
	int _currentHeight = 0;
	int _lastPosX = 0;
	int _lastPosY = 0;
	bool _windowed = true;
	const char* _title = "OpenGL Renderer";
	GLFWwindow* _window;
	GLFWmonitor* _monitor;
	const GLFWvidmode* _vidmode;
	OPGLRWindow* _windowClass;
}


// Declare callbacks
void resize(GLFWwindow*, int width, int height);
void scroll(GLFWwindow*, double xoffset, double yoffset);


void Window::Init(int width, int height, const char* title) {
	// Initialize GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return;
	}

	// Create a new window instance
	_windowClass = new OPGLRWindow();

	// Set the windows dimensions and title
	_currentWidth = width;
	_currentHeight = height;
	_title = title;

	// Set minimized windows dimensions
	_windowClass->SetMinimizedWindowSize(width, height);

	// Get our fullscreen dimensions
	_monitor = glfwGetPrimaryMonitor();
	_vidmode = glfwGetVideoMode(_monitor);
	_windowClass->SetFullscreenSize(_vidmode->width, _vidmode->height);

	// Tell GLFW things about our monitor
	glfwWindowHint(GLFW_RED_BITS, _vidmode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, _vidmode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, _vidmode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, _vidmode->refreshRate);

	// Tell GLFW our OpenGL Version, so that we don't enable backwards compability
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create our Window using GLFW, terminate if this fails
	_window = glfwCreateWindow(_currentWidth, _currentHeight, _title, NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// Make the Window our current context
	glfwMakeContextCurrent(_window);

	// Initialize GLAD and terminate if this fails
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// We have to specify a viewport for OpenGL
	glViewport(0, 0, _currentWidth, _currentHeight);

	// Add callbacks to our Window
	glfwSetWindowSizeCallback(_window, resize);
	glfwSetScrollCallback(_window, scroll);
}

void Window::Render() {
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

GLFWwindow* Window::GetWindow() {
	return _window;
}

void Window::ToggleFullscreen() {
	_windowClass->ToggleWindowed();
	if (!_windowClass->GetWindowed()) {
		// Store window positions and fullscreen the window
		glfwGetWindowPos(_window, &_windowClass->lastPosX, &_windowClass->lastPosY);
		screenSize size = _windowClass->GetFullscreenSize();
		glfwSetWindowMonitor(_window, _monitor, 0, 0, size.width, size.height, _vidmode->refreshRate);
	}
	else {
		// Restore window to minimized dimensions and set to stored position
		screenSize size = _windowClass->GetMinimizedWindowsSize();
		std::cout << size.width << std::endl;
		std::cout << size.height << std::endl;
		glfwSetWindowMonitor(_window, nullptr, 0, 0, size.width, size.height, 0);
		glfwSetWindowPos(_window, _windowClass->lastPosX, _windowClass->lastPosY);
	}
}


/*
	Callbacks
*/

void resize(GLFWwindow*, int width, int height) {
	glViewport(0, 0, width, height);
	if (Window::_windowClass->GetWindowed()) {
		Window::_windowClass->SetMinimizedWindowSize(width, height);
	}
}
void scroll(GLFWwindow*, double xoffset, double yoffset) {
	// do stuff
}