#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "ShaderProgram.h"

namespace eyesore {
	class Camera {
		public:
			Camera(glm::vec3 position, glm::vec3 direction, GLfloat aspectRatio,
					GLfloat fov = 45.0f);

			void use() const;

		private:
			glm::vec3 position, direction, right, up;
			GLfloat aspectRatio, fov;
			GLfloat near = 0.1f, far = 1000.0f;
	};
}

#endif

