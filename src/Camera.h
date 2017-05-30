#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include "ShaderProgram.h"

namespace eyesore {
	class Camera {
		public:
			Camera(glm::vec3 position, GLfloat aspectRatio, GLfloat fov = 45.0f);

			void use();

			void move(glm::vec2 v);
			void setPitch(GLfloat delta);
			void setYaw(GLfloat delta);

			glm::mat4 getView();
			glm::mat4 getProjection();

		private:
			glm::vec3 position, front, right, up;
			glm::vec3 velocity, acceleration;
			GLfloat pitch = 0.0f, yaw = 0.0f;
			GLfloat aspectRatio, fov;
			GLfloat near = 0.01f, far = 10000.0f;

			void update();
			void orient();
	};
}

#endif

