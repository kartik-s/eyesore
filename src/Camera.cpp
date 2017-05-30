#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/common.hpp>
#include <glm/ext.hpp>
#include "Camera.h"

using namespace eyesore;

using glm::vec2;
using glm::vec3;
using glm::mat4;
using glm::cos;
using glm::sin;

eyesore::Camera::Camera(vec3 position, GLfloat aspectRatio, GLfloat fov):
	position(position), aspectRatio(aspectRatio), fov(fov)
{
	orient();
}

mat4 eyesore::Camera::getView()
{
	return glm::lookAt(position, position + front, up);
}

mat4 eyesore::Camera::getProjection()
{
	return glm::perspective(fov, aspectRatio, near, far);
}

void eyesore::Camera::update()
{
	if (glm::length(acceleration) == 0.0f) {
		velocity /= 2.0f;

		if (glm::length(velocity) <= 0.1f)
			velocity = vec3(0.0f, 0.0f, 0.0f);
	} else {
		GLfloat speed = glm::length(velocity);

		if (speed > 1)
			velocity = glm::normalize(velocity);
		else
			velocity += acceleration;
	}

	position += velocity;
}

void eyesore::Camera::use()
{
	GLint program;

	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	mat4 view = getView();
	mat4 projection = getProjection();

	mat4 model;

	model = glm::scale(model, vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, vec3(0.0f, 0.0f, 0.0f));

	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projectionLoc = glGetUniformLocation(program, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	GLint pLoc = glGetUniformLocation(program, "p");

	glUniform3fv(pLoc, 1, glm::value_ptr(position));
}

void eyesore::Camera::move(vec2 v)
{
	acceleration = v.y * front + v.x * right;
	update();
}

void eyesore::Camera::setPitch(GLfloat delta)
{
	pitch = glm::clamp(pitch + delta/50.0f, -1.57f, 1.57f);
	orient();
}

void eyesore::Camera::setYaw(GLfloat delta)
{
	yaw = glm::fmod(yaw + delta/50.0f, 6.28f);
	orient();
}

void eyesore::Camera::orient()
{
	front = vec3(cos(pitch)*cos(yaw), sin(pitch), cos(pitch)*sin(yaw));
	right = glm::normalize(glm::cross(front, vec3(0.0f, 1.0f, 0.0f)));
	up = glm::normalize(glm::cross(right, front));
}

