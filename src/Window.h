#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GLFW/glfw3.h>

namespace eyesore {
	class Window {
		public:
			Window(int width, int height, std::string &title, bool fullscreen);
			~Window();

			GLFWwindow *get();

		private:
			GLFWwindow *window;
	};
}

#endif

