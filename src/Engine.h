#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "Window.h"

namespace eyesore {
	class Engine {
		public:
			Engine();
			~Engine();

			void makeWindow(int height, int width, std::string title,
					bool fullscreen);
			void run();

		private:
			eyesore::Window *window;
	};
}

#endif

