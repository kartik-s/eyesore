#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include <GL/glew.h>

#include "Model.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Environment.h"

namespace eyesore {
	class Scene {
		public:
			Scene(std::string path, eyesore::Camera *camera);

			void add(eyesore::Model model);
			void render();

		private:
			GLint width, height;

			std::vector<eyesore::Model> models;
			eyesore::ShaderProgram shader;
			eyesore::Environment *environment;
			eyesore::Camera *camera;
	};
}

#endif

