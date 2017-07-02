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
			int m_xoff, m_yoff;
			int m_defaultWidth, m_defaultHeight;
			float m_screenRatio;
			GLFWwindow* m_wnd;
			bool m_fullscreen;
		
		public:
			Window(const char* name, int width, int height);
			~Window();
			bool shouldClose() const;
			void drawStart();
			void drawEnd();

			// Sets window icons from PNG or other image files.
			// For instance, files logo16.png, logo32.png and logo64.png.
			void setWindowIcons(std::vector<std::string> names);
			void setWindowTitle(const std::string& title);

			inline void setFullscreen(bool fullscreen) { m_fullscreen = fullscreen; updateFullscreen(); }
			inline void toggleFullscreen() { m_fullscreen = !m_fullscreen; updateFullscreen(); }

			inline int getW() { return m_width; }
			inline int getH() { return m_height; }
			inline int getDefaultW() { return m_defaultWidth; }
			inline int getDefaultH() { return m_defaultHeight; }
			inline int getXoff() { return m_xoff; }
			inline int getYoff() { return m_yoff; }
		private:
			void init();
			void updateFullscreen();
			friend void windowResizeCallback(GLFWwindow* window, int width, int height);
		};
	}
}