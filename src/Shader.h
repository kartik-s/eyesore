#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>

namespace eyesore {
	class Shader {
		public:
			Shader(const std::string path, GLenum type);
			~Shader();

			GLuint get();

		private:
			GLuint id;
	};
}

#endif
