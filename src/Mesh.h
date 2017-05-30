#ifndef MESH_H
#define MESH_H

#include <vector>
#include <memory>

#include <GL/glew.h>
#include <assimp/scene.h>

#include "Vertex.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Material.h"

namespace eyesore {
	class Model;

	class Mesh {
		public:
			Mesh(std::vector<eyesore::Vertex> vertices,
					std::vector<GLuint> indices);

			void render();
			void render(eyesore::Camera &camera, eyesore::Material &material);

		private:
			std::vector<eyesore::Vertex> vertices;
			std::vector<GLuint> indices;

			GLuint vao, vbo, ebo;	
	};
}

#endif

