#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Model.h"
#include "Camera.h"

namespace eyesore {
	class Scene {
		public:
			void add(eyesore::Model model);
			void render(eyesore::Camera &camera) const;

		private:
			std::vector<eyesore::Model> models;
	};
}

#endif

