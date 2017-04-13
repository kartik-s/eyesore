#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>

#include "Shader.h"

namespace eyesore {
	class ShaderProgram {
		public:
			ShaderProgram();
			~ShaderProgram();

			void attach(eyesore::Shader shader);
			void use() const;

		private:
			GLuint id;
	};
}

#endif

