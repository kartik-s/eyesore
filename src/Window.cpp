#include <GL/glew.h>

#include "Window.h"

using std::string;

eyesore::Window::Window(int width, int height, string &title, bool fullscreen)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, title.c_str(),
			fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
}

eyesore::Window::~Window()
{
	glfwDestroyWindow(window);
}

GLFWwindow *eyesore::Window::get() const
{
	return window;
}

