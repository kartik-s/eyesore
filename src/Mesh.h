#ifndef MESH_H
#define MESH_H

#include <vector>

#include <GL/glew.h>
#include <assimp/scene.h>

#include "Vertex.h"
#include "ShaderProgram.h"
#include "Camera.h"

namespace eyesore {
	class Mesh {
		public:
			Mesh(std::vector<eyesore::Vertex> vertices,
					std::vector<GLuint> indices);
			~Mesh();

			void render(eyesore::ShaderProgram &shader, eyesore::Camera &camera) const;

		private:
			std::vector<eyesore::Vertex> vertices;
			std::vector<GLuint> indices;

			GLuint vao, vbo, ebo;
	};
}

#endif

