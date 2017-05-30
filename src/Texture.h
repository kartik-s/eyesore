#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>

namespace eyesore {
	class Texture {
		public:
			Texture(std::string path);

			GLuint get() const;

		private:
			GLuint id;
	};
}

#endif

