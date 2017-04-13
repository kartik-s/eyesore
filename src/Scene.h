#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Model.h"
#include "Camera.h"

namespace eyesore {
	class Scene {
		public:
			Scene(eysore::Camera camera);
			void add(eyesore::Model model);
			void render() const;

		private:
			std::vector<eyesore::Model> models;
			eyesore::Camera camera;
	};
}

#endif

