#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace eyesore {
	class Camera {
		public:
			Camera(glm::vec3 position, glm::vec3 direction);
			
		private:
			glm::vec3 position, direction, right, up;
	};
}

#endif

