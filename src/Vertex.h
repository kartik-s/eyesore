#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace eyesore {
	class Vertex {
		public:
			glm::vec3 position, normal;
			glm::vec2 uv;

			Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv);
			Vertex(glm::vec3 position, glm::vec2 uv);
	};
}

#endif

