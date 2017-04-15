#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "Mesh.h"
#include "Camera.h"

namespace eyesore {
	class Model {
		public:
			Model(const std::string &path);

			void render(eyesore::Camera &camera) const;

		private:
			std::vector<Mesh> meshes;

			static eyesore::Mesh extractMesh(const aiMesh *mesh);
	};
}

#endif

