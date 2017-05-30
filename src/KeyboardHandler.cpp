#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include "KeyboardHandler.h"

using namespace eyesore;

using glm::vec2;

eyesore::KeyboardHandler::KeyboardHandler(Window *window, Camera *camera):
	window(window), camera(camera)
{

}

void eyesore::KeyboardHandler::setWindow(Window *window)
{
	this->window = window;
}

void eyesore::KeyboardHandler::dispatch()
{
	GLFWwindow *w = window->get();
	vec2 v(0.0f, 0.0f);

	if (glfwGetKey(w, GLFW_KEY_W))
		v += vec2(0.0f, 0.01f);
	
	if (glfwGetKey(w, GLFW_KEY_S))
		v += vec2(0.0f, -0.01f);

	if (glfwGetKey(w, GLFW_KEY_A))
		v += vec2(-0.01f, 0.0f);

	if (glfwGetKey(w, GLFW_KEY_D))
		v += vec2(0.01f, 0.0f);

	camera->move(glm::length(v) == 0.0f ? v : glm::normalize(v));

	GLfloat pitch = 0.0f;

	if (glfwGetKey(w, GLFW_KEY_UP))
		pitch += 0.01f;

	if (glfwGetKey(w, GLFW_KEY_DOWN))
		pitch += -0.01f;

	camera->setPitch(pitch);

	GLfloat yaw = 0.0f;

	if (glfwGetKey(w, GLFW_KEY_LEFT))
		yaw += -0.01f;

	if (glfwGetKey(w, GLFW_KEY_RIGHT))
		yaw += 0.01f;

	camera->setYaw(yaw);
}

