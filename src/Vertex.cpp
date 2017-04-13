#include <glm/glm.hpp>

#include "Vertex.h"

using glm::vec2;
using glm::vec3;

eyesore::Vertex::Vertex(vec3 position, vec3 normal, vec2 uv):
	position(position), normal(normal), uv(uv)
{

}

eyesore::Vertex::Vertex(vec3 position, vec2 uv):
	position(position), uv(uv)
{

}

