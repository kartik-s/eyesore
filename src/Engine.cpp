#include <iostream>
#include <string>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "Window.h"
#include "KeyboardHandler.h"

using namespace eyesore;

using std::cerr;
using std::endl; using std::string;
using std::exit;

void errorHandler(int error, const char *description)
{
	cerr << "GLFW: " << description << endl;

	glfwTerminate();
	exit(EXIT_FAILURE);
}

eyesore::Engine::Engine(Camera *camera): camera(camera), input(nullptr, camera)
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

	input.setWindow(window);
}

void eyesore::Engine::run(Scene &scene)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glDepthFunc(GL_LEQUAL);

	while (!glfwWindowShouldClose(window->get())) {
		glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		input.dispatch();
		scene.render();

		glfwSwapBuffers(window->get());
		glfwPollEvents();
	}
}

