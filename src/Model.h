#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "Mesh.h"

namespace eyesore {
	class Model {
		public:
			Model(const std::string &path);
			~Model();

			void render();

		private:
			std::vector<Mesh> meshes;
	};
}

#endif

