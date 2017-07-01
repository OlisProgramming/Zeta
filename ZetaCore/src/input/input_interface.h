#pragma once

#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

namespace zeta {
	namespace input {

#define KEYS_MAX		1024
#define BUTTONS_MAX		32

		struct KeyData {
			bool thisframe : 1;  // Using bitfields to save space
			bool lastframe : 1;
			bool tempframe : 1;
		};

		class InputInterface {

		public:
			static InputInterface* inst;
		private:
			KeyData m_keys[KEYS_MAX];
			KeyData m_buttons[BUTTONS_MAX];
			double m_mouseX, m_mouseY;

		public:
			InputInterface();
			inline bool keyPressed(int keycode) const { return m_keys[keycode].thisframe && !m_keys[keycode].lastframe; }
			inline bool btnPressed(int btncode) const { return m_buttons[btncode].thisframe && !m_buttons[btncode].lastframe; }
			inline bool keyDown(int keycode) const { return m_keys[keycode].thisframe; }
			inline bool btnDown(int btncode) const { return m_buttons[btncode].thisframe; }
			inline bool keyReleased(int keycode) const { return m_keys[keycode].lastframe && !m_keys[keycode].thisframe; }
			inline bool btnReleased(int btncode) const { return m_buttons[btncode].lastframe && !m_buttons[btncode].thisframe; }
			inline int mouseX() const { return (int)m_mouseX; }
			inline int mouseY() const { return (int)m_mouseY; }
			inline glm::vec2 mousePos() const { return glm::vec2(m_mouseX, m_mouseY); }
			void registerEvents(GLFWwindow* wnd) const;
			void update();
		private:
			friend void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void windowBtnCallback(GLFWwindow* window, int button, int action, int mods);
			friend void windowCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}