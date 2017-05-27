#pragma once

#include <GLFW\glfw3.h>

namespace zeta {
	namespace input {

#define KEYS_MAX		1024
#define BUTTONS_MAX		32

		class InputInterface {

		public:
			static InputInterface* inst;
		private:
			bool m_keys[KEYS_MAX];
			bool m_buttons[BUTTONS_MAX];
			double m_mouseX, m_mouseY;

		public:
			InputInterface();
			inline bool keyPressed(int keycode) const { return m_keys[keycode]; }
			inline bool btnPressed(int btncode) const { return m_buttons[btncode]; }
			inline int mouseX() const { return (int)m_mouseX; }
			inline int mouseY() const { return (int)m_mouseY; }
			void registerEvents(GLFWwindow* wnd) const;
		private:
			friend void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void windowBtnCallback(GLFWwindow* window, int button, int action, int mods);
			friend void windowCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}