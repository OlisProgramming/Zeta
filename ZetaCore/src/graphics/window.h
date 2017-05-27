#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace zeta {
	namespace graphics {

		class Window {
		public:
			static Window* inst;
		private:
			const char* m_title;
			int m_width, m_height;
			GLFWwindow* m_wnd;
		
		public:
			Window(const char* name, int width, int height);
			~Window();
			bool shouldClose() const;
			void drawStart();
			void drawEnd();
		private:
			void init();
			friend void windowResizeCallback(GLFWwindow* window, int width, int height);
		};
	}
}