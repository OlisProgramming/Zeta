#include "input_interface.h"

namespace zeta {
	namespace input {

		InputInterface* InputInterface::inst;
		void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void windowBtnCallback(GLFWwindow* window, int button, int action, int mods);
		void windowCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

		InputInterface::InputInterface() : m_mouseX(0.0), m_mouseY(0.0) {
			inst = this;
			for (unsigned int i = 0; i < KEYS_MAX; ++i) {
				m_keys[i].thisframe = false;
				m_keys[i].lastframe = false;
				m_keys[i].tempframe = false;
			}
			for (unsigned int i = 0; i < BUTTONS_MAX; ++i) {
				m_buttons[i].thisframe = false;
				m_buttons[i].lastframe = false;
				m_buttons[i].tempframe = false;
			}
		}

		void InputInterface::registerEvents(GLFWwindow* wnd) const {
			glfwSetKeyCallback(wnd, windowKeyCallback);
			glfwSetCursorPosCallback(wnd, windowCursorPosCallback);
			glfwSetMouseButtonCallback(wnd, windowBtnCallback);
		}

		void InputInterface::update() {
			for (unsigned int i = 0; i < KEYS_MAX; ++i) {
				m_keys[i].lastframe = m_keys[i].thisframe;
			}
			for (unsigned int i = 0; i < BUTTONS_MAX; ++i) {
				m_buttons[i].lastframe = m_buttons[i].thisframe;
			}
			for (unsigned int i = 0; i < KEYS_MAX; ++i) {
				m_keys[i].thisframe = m_keys[i].tempframe;
			}
			for (unsigned int i = 0; i < BUTTONS_MAX; ++i) {
				m_buttons[i].thisframe = m_buttons[i].tempframe;
			}
		}

		void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			InputInterface::inst->m_keys[key].tempframe = static_cast<bool>(action != GLFW_RELEASE);
		}

		void windowBtnCallback(GLFWwindow* window, int button, int action, int mods) {
			InputInterface::inst->m_buttons[button].tempframe = static_cast<bool>(action != GLFW_RELEASE);
		}

		void windowCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
			InputInterface::inst->m_mouseX = xpos;
			InputInterface::inst->m_mouseY = ypos;
		}
	}
}