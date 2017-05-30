#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include "Texture.h"

namespace eyesore {
	class Material {
		public:
			Material(std::string name);

			void use();

		private:
			eyesore::Texture *albedo, *normal, *metallic, *roughness;

			static const std::string MATERIAL_PATH;
	};
}

#endif

