#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include "../input/input_interface.h"
#include "../sound/sound_manager.h"
#include "texture\texture_manager.h"
#include "font\font_manager.h"
#include "renderer\renderer.h"

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
			glfwSetFramebufferSizeCallback(m_wnd, windowResizeCallback);
			glfwSwapInterval(0);
			
			if (glewInit() != GLEW_OK) {
				fprintf(stderr, "GLEW could not initialise!\n");
				system("pause");
				exit(-1);
				return;
			}

			// Register static managers and interfaces
			new input::InputInterface;
			input::InputInterface::inst->registerEvents(m_wnd);
			new sound::SoundManager;
			new FontManager;
			new TextureManager;

			printf("Zeta is using OpenGL %s\n", glGetString(GL_VERSION));

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			// Set up static IBOs
			Renderer::init();
		}

		Window::~Window() {
			// Delete static managers and interfaces
			delete input::InputInterface::inst;
			sound::SoundManager::inst->cleanup();
			delete sound::SoundManager::inst;
			FontManager::inst->cleanup();
			delete FontManager::inst;
			delete TextureManager::inst;

			glfwDestroyWindow(m_wnd);
			glfwTerminate();
		}

		bool Window::shouldClose() const {
			return glfwWindowShouldClose(m_wnd);
		}

		void Window::drawStart() {
			input::InputInterface::inst->update();
			sound::SoundManager::inst->update();
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
