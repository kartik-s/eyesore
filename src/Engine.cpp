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

eyesore::Engine::Engine(Camera camera): camera(camera)
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

	glewExperimental = GL_TRUE;
	glewInit();

	int w, h;

	glfwGetFramebufferSize(window->get(), &w, &h);
	glViewport(0, 0, w, h);
}

void eyesore::Engine::setScene(Scene scene)
{
	this->scene = scene;
}

void eyesore::Engine::run()
{
	while (!glfwWindowShouldClose(window->get())) {
		glClear(GL_COLOR_BUFFER_BIT);

		scene.render(camera);

		glfwSwapBuffers(window->get());
		glfwPollEvents();
	}
}

