#include "Camera.h"

using namespace eyespre;
using namespace glm;

eyesore::Camera::Camera(vec3 position, vec3 direction):
	position(position), direction(normalize(direction))
{
	right = normalize(cross(direction, vec3(0, 1, 0)));
	up = normalize(cross(right, direction));
}

