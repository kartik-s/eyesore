#include <iostream>
#include <string>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine.h"
#include "Window.h"

using namespace eyesore;

using std::cerr;
using std::endl;
using std::string;
using std::exit;

void errorHandler(int error, const char *description)
{
	cerr << "GLFW: " << description << endl;

	glfwTerminate();
	exit(EXIT_FAILURE);
}

eyesore::Engine::Engine()
{
	glfwSetErrorCallback(errorHandler);
	glfwInit();
}

eyesore::Engine::~Engine()
{
	delete window;

	glfwTerminate();
}

void eyesore::Engine::makeWindow(int width, int height, string title, bool fullscreen)
{
	window = new Window(width, height, title, fullscreen);

	glfwMakeContextCurrent(window->get());
}

void eyesore::Engine::run()
{
	while (!glfwWindowShouldClose(window->get())) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window->get());

		glfwPollEvents();
	}
}

