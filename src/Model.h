#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Camera.h"
#include "Material.h"

namespace eyesore {
	class Scene;

	class Model {
		public:
			Model(std::string description);

			void render();
			void render(eyesore::Camera &camera);

		private:
			eyesore::Material *material;
			std::vector<Mesh> meshes;

			glm::vec3 position, scale = glm::vec3(1.0f, 1.0f, 1.0f);
			glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
			GLfloat angle = 0.0f;

			void load(const std::string &path);
			static eyesore::Mesh extract(const aiMesh *mesh);

			static const std::string MODEL_PATH;
	};
}

#endif

