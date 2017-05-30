#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Model.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Camera.h"

namespace eyesore {
	class Environment {
		public:
			Environment(std::string path, eyesore::Camera *camera);

			void use();
			void render();

		private:
			GLuint hdri, cubemap, irradiance, prefilter, brdfLUT;
			eyesore::ShaderProgram skybox;
			const static std::string ENV_PATH;
			const static GLsizei CUBEMAP_RES = 512;
			eyesore::Model cube;
			eyesore::Camera *camera;

			void makeMaps();
			void makeCubemap(GLuint fbo, GLuint rbo, glm::mat4 projection, glm::mat4 *views);
			void makeIrradianceMap(GLuint fbo, GLuint rbo, glm::mat4 projection, glm::mat4 *views);
			void makePrefilterMap(GLuint fbo, GLuint rbo, glm::mat4 projection, glm::mat4 *views);
			void makeBRDFLUT(GLuint fbo, GLuint rbo);
	};
}

#endif

