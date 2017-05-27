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
				m_keys[i] = false;
			}
			for (unsigned int i = 0; i < BUTTONS_MAX; ++i) {
				m_buttons[i] = false;
			}
		}

		void InputInterface::registerEvents(GLFWwindow* wnd) const {
			glfwSetKeyCallback(wnd, windowKeyCallback);
			glfwSetCursorPosCallback(wnd, windowCursorPosCallback);
			glfwSetMouseButtonCallback(wnd, windowBtnCallback);
		}

		void windowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			InputInterface::inst->m_keys[key] = static_cast<bool>(action != GLFW_RELEASE);
		}

		void windowBtnCallback(GLFWwindow* window, int button, int action, int mods) {
			InputInterface::inst->m_buttons[button] = static_cast<bool>(action != GLFW_RELEASE);
		}

		void windowCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
			InputInterface::inst->m_mouseX = xpos;
			InputInterface::inst->m_mouseY = ypos;
		}
	}
}