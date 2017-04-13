#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "Mesh.h"

namespace eyesore {
	class Model {
		public:
			Model(const std::string &path);

			void render() const;

		private:
			std::vector<Mesh> meshes;

			static eyesore::Mesh extractMesh(const aiMesh *mesh);
	};
}

#endif

