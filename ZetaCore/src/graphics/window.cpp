#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include "../input/input_interface.h"

namespace zeta {
	namespace graphics {

		Window* Window::inst;
		void windowResizeCallback(GLFWwindow* window, int width, int height);

		Window::Window(const char* title, int width, int height) :
			m_title(title), m_width(width), m_height(height), m_wnd(NULL) {
			inst = this;
			init();
		}

		void Window::init() {
			if (!glfwInit()) {
				fprintf(stderr, "GLFW could not initialise!\n");
				system("pause");
				exit(-1);
				return;
			}

			m_wnd = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_wnd) {
				fprintf(stderr, "GLFW window could not initialise!\n");
				system("pause");
				exit(-1);
				return;
			}
			glfwMakeContextCurrent(m_wnd);
			glfwSetWindowUserPointer(m_wnd, this);
			glfwSetWindowSizeCallback(m_wnd, windowResizeCallback);
			
			if (glewInit() != GLEW_OK) {
				fprintf(stderr, "GLEW could not initialise!\n");
				system("pause");
				exit(-1);
				return;
			}

			(new input::InputInterface)->registerEvents(m_wnd);

			printf("Zeta is using OpenGL %s\n", glGetString(GL_VERSION));

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			//glEnable(GL_DEPTH_TEST);
		}

		Window::~Window() {
			glfwDestroyWindow(m_wnd);
			glfwTerminate();
		}

		bool Window::shouldClose() const {
			return glfwWindowShouldClose(m_wnd);
		}

		void Window::drawStart() {
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::drawEnd() {
			glfwSwapBuffers(m_wnd);

			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				printf("OpenGL Error: %d\n", error);
		}

		void windowResizeCallback(GLFWwindow* window, int width, int height) {
			Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
			glViewport(0, 0, width, height);
			glfwGetFramebufferSize(wnd->m_wnd, &(wnd->m_width), &(wnd->m_height));
		}
	}
}