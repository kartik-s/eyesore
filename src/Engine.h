#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "Scene.h"
#include "Camera.h"
#include "Window.h"

namespace eyesore {
	class Engine {
		public:
			Engine(eyesore::Camera camera);
			~Engine();

			void makeWindow(int height, int width, std::string title,
					bool fullscreen);
			void setScene(eyesore::Scene scene);
			void run();

		private:
			eyesore::Window *window;
			eyesore::Scene scene;
			eyesore::Camera camera;
	};
}

#endif

