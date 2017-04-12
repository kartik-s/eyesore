#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include <GL/glew.h>

#include "Vertex.h"

namespace eyesore {
	class Mesh {
		public:
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);

			void render() const;

		private:
			std::vector<Vertex> vertices;
			std::vector<GLuint> indices;

			GLuint vao, vbo, ebo;
	};
}

#endif

