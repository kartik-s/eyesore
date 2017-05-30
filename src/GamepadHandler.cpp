#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GamepadHandler.h"

#include <iostream>
#include <cmath>

using namespace eyesore;

using glm::vec2;

eyesore::GamepadHandler::GamepadHandler(Window *window, Camera *camera):
	window(window), camera(camera)
{

}

void eyesore::GamepadHandler::setWindow(Window *window)
{
	this->window = window;
}

void eyesore::GamepadHandler::dispatch()
{
	GLFWwindow *w = window->get();

	int count;
	const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);

	float x, y;

	if (std::abs(axes[0]) < 0.25)
		x = 0.0f;
	else
		x = axes[0];

	if (std::abs(axes[1]) < 0.25)
		y = 0.0f;
	else
		y = axes[1];

	vec2 v(x, -y);

	camera->move(glm::length(v) == 0.0f ? v : glm::normalize(v));

	if (std::abs(axes[4]) < 0.25)
		x = 0.0f;
	else
		x = axes[4];

	if (std::abs(axes[3]) < 0.25)
		y = 0.0f;
	else
		y = axes[3];


	camera->setPitch(-x);
	camera->setYaw(y);
}

