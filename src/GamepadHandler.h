#ifndef GAMEPAD_HANDLER_H
#define GAMEPAD_HANDLER_H

#include "Window.h"
#include "Camera.h"

namespace eyesore {
	class GamepadHandler {
		public:
			GamepadHandler(eyesore::Window *window, eyesore::Camera *camera);

			void setWindow(eyesore::Window *window);
			void dispatch();
			
		private:
			eyesore::Window *window;
			eyesore::Camera *camera;
	};
}

#endif

