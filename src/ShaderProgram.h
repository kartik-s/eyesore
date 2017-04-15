#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>

#include "Shader.h"

namespace eyesore {
	class ShaderProgram {
		public:
			ShaderProgram();
			~ShaderProgram();

			GLuint get() const;
			void attach(eyesore::Shader shader);
			void link() const;
			void use() const;

		private:
			GLuint id;
	};
}

#endif

