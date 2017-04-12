#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

namespace eyesore {
	class Vertex {
		public:
			Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv);

		private:
			glm::vec3 position, normal;
			glm::vec2 uv;
	};
}

#endif

