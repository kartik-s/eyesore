#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include "Window.h"
#include "Camera.h"

namespace eyesore {
	class KeyboardHandler {
		public:
			KeyboardHandler(eyesore::Window *window, eyesore::Camera *camera);

			void setWindow(eyesore::Window *window);
			void dispatch();
			
		private:
			eyesore::Window *window;
			eyesore::Camera *camera;
	};
}

#endif

