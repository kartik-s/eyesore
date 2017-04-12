#include "Window.h"

using std::string;

eyesore::Window::Window(int width, int height, string &title, bool fullscreen)
{
	window = glfwCreateWindow(width, height, title.c_str(),
			fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
}

eyesore::Window::~Window()
{
	glfwDestroyWindow(window);
}

GLFWwindow *eyesore::Window::get()
{
	return window;
}

