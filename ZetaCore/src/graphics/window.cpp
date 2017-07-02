#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include "../input/input_interface.h"
#include "../sound/sound_manager.h"
#include "../level/global_data.h"
#include "../entity/behaviour_factory.h"
#include "../util/image_load.h"
#include "../game/save.h"
#include "texture\texture_manager.h"
#include "texture\tileset_manager.h"
#include "font\font_manager.h"
#include "renderer\renderer.h"
#include "../util/logging.h"

namespace zeta {
	namespace graphics {

		Window* Window::inst;
		void windowResizeCallback(GLFWwindow* window, int width, int height);

		Window::Window(const char* title, int width, int height) :
			m_title(title), m_width(width), m_height(height), m_defaultWidth(width), m_defaultHeight(height), m_wnd(NULL) {
			inst = this;
			m_screenRatio = (float)width / (float)height;
			init();
		}

		void Window::setWindowIcons(std::vector<std::string> names) {

			std::vector<GLFWimage> logos;
			std::vector<FIBITMAP*> dibs;
			for (const std::string& name : names) {
				
				FIBITMAP* dib;
				unsigned int w, h;
				util::IMAGE_DATA logo = util::loadImage(name.c_str(), w, h, &dib);
				util::flipBlueRed(logo, w, h);
				util::flipY(logo, w, h);
				GLFWimage glfwLogo;
				glfwLogo.pixels = logo;
				glfwLogo.width = w;
				glfwLogo.height = h;
				logos.push_back(glfwLogo);
				dibs.push_back(dib);
			}

			glfwSetWindowIcon(m_wnd, logos.size(), &logos[0]);
			
			for (FIBITMAP* dib : dibs) {
				FreeImage_Unload(dib);
			}
		}

		void Window::setWindowTitle(const std::string& title) {
			glfwSetWindowTitle(m_wnd, title.c_str());
		}

		void Window::init() {
			if (!glfwInit()) {
				fprintf(stderr, "GLFW could not initialise!\n");
				system("pause");
				exit(-1);
				return;
			}

			//glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

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

			setWindowIcons({
				"../res/internal/logo16.png",
				"../res/internal/logo32.png",
				"../res/internal/logo64.png"
			});

			// Register static managers and interfaces
			new input::InputInterface;
			input::InputInterface::inst->registerEvents(m_wnd);
			new sound::SoundManager;
			new FontManager;
			new TextureManager;
			new TilesetManager;
			new level::GlobalData;
			new entity::BehaviourFactory;

			ZLog("Zeta is using OpenGL " + std::string((char*)glGetString(GL_VERSION)) + ".");

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CW);
			
			// Set up static IBOs
			Renderer::init();
		}

		void Window::updateFullscreen() {
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			if (m_fullscreen) {
				// Set window size for "fullscreen windowed" mode to the desktop resolution.
				glfwSetWindowSize(m_wnd, mode->width, mode->height);
				// Move window to the upper left corner.
				glfwSetWindowPos(m_wnd, 0, 0);
			}
			else {
				// Use start-up values for "windowed" mode.
				glfwSetWindowSize(m_wnd, m_defaultWidth, m_defaultHeight);
				glfwSetWindowPos(m_wnd, 32, 32);
			}
		}

		Window::~Window() {
			// Delete static managers and interfaces
			delete input::InputInterface::inst;
			sound::SoundManager::inst->cleanup();
			delete sound::SoundManager::inst;
			FontManager::inst->cleanup();
			delete FontManager::inst;
			delete TextureManager::inst;
			delete TilesetManager::inst;
			delete level::GlobalData::inst;

			glfwDestroyWindow(m_wnd);
			glfwTerminate();
		}

		bool Window::shouldClose() const {
			bool a = glfwWindowShouldClose(m_wnd);
			return a;
		}

		void Window::drawStart() {
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
			float thisScreenRatio = (float)width / (float)height;
			int newX, newY;
			int newW, newH;
			if (thisScreenRatio > wnd->m_screenRatio) {  // Black bars on left and right
				newW = (int)((float)height * wnd->m_screenRatio);
				newH = height;
				newX = (width - newW) / 2;
				newY = 0;
			}
			else {  // Black bars on top and bottom
				newW = width;
				newH = (int)((float)width / wnd->m_screenRatio);
				newX = 0;
				newY = (height - newH) / 2;
			}
			glViewport(newX, newY, newW, newH);
			glfwGetFramebufferSize(wnd->m_wnd, &(wnd->m_width), &(wnd->m_height));
		}
	}
}
