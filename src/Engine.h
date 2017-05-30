#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "Window.h"
#include "Scene.h"
#include "Camera.h"
#include "KeyboardHandler.h"
#include "GamepadHandler.h"

namespace eyesore {
	class Engine {
		public:
			Engine(eyesore::Camera *camera);
			~Engine();

			void makeWindow(int height, int width, std::string title,
					bool fullscreen);
			void run(eyesore::Scene &scene);

		private:
			eyesore::Window *window;
			eyesore::Camera *camera;
			eyesore::GamepadHandler input;
	};
}

#endif

