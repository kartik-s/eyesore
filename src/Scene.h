#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Model.h"

namespace eyesore {
	class Scene {
		public:
			void add(eyesore::Model model);
			void render() const;

		private:
			std::vector<eyesore::Model> models;
	};
}

#endif

