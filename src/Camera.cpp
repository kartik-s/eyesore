#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

using namespace eyesore;

using glm::vec3;
using glm::mat4;

eyesore::Camera::Camera(vec3 position, vec3 direction, GLfloat aspectRatio,
		GLfloat fov):
	position(position), direction(normalize(direction)), aspectRatio(aspectRatio),
	fov(fov)
{
	right = normalize(cross(direction, vec3(0, 1, 0)));
	up = normalize(cross(right, direction));
}

void eyesore::Camera::use() const
{
	GLint program;

	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	mat4 view = glm::lookAt(position, position + direction, up);
	mat4 projection = glm::perspective(fov, aspectRatio, near, far);
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projectionLoc = glGetUniformLocation(program, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

