#ifndef MESH_H
#define MESH_H

#include <vector>

#include <GL/glew.h>
#include <assimp/scene.h>

#include "Vertex.h"
#include "ShaderProgram.h"

namespace eyesore {
	class Mesh {
		public:
			Mesh(std::vector<eyesore::Vertex> vertices,
					std::vector<GLuint> indices);

			void setShader(eyesore::ShaderProgram shader);
			void render() const;

		private:
			std::vector<eyesore::Vertex> vertices;
			std::vector<GLuint> indices;

			GLuint vao, vbo, ebo;
			eyesore::ShaderProgram shader;
	};
}

#endif

