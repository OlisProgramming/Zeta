#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <string>

namespace zeta {
	namespace graphics {

		class Window {
		public:
			static Window* inst;
		private:
			const char* m_title;
			int m_width, m_height;
			float m_screenRatio;
			GLFWwindow* m_wnd;
		
		public:
			Window(const char* name, int width, int height);
			~Window();
			bool shouldClose() const;
			void drawStart();
			void drawEnd();

			// Sets window icons from PNG or other image files.
			// For instance, files logo16.png, logo32.png and logo64.png.
			void setWindowIcons(std::vector<std::string> names);
		private:
			void init();
			friend void windowResizeCallback(GLFWwindow* window, int width, int height);
		};
	}
}