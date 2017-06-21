#include "game.h"

#include "../graphics/shader/shader_basic.h"
#include "../entity/behaviour_factory.h"
#include "../entity/behaviours_builtin.h"
#include "../level/global_data.h"
#include "../util/fps_clock.h"

namespace zeta {
	namespace game {

		using namespace util;

		Game* Game::inst;

		Game::Game(const std::string& name, int width, int height) {
			inst = this;

			m_levelShouldChange = false;

#ifdef ZETA_CONFIG_RELEASE
# ifdef _WIN32
			FreeConsole();
# endif
#endif

			new graphics::Window(name.c_str(), width, height);
			m_shader = new graphics::ShaderBasic;
			m_renderer = new graphics::Renderer(m_shader);
			m_camera = new graphics::Camera(m_shader, { width, height });

#ifdef ZETA_CONFIG_DEBUG
			m_fpsCounter = new graphics::Label("100 FPS", { 5, 20, 400000.0f }, true);
#endif

			registerBehaviours();
		}

		Game::~Game() {
			delete m_level;
			delete m_camera;
			delete m_renderer;
#ifdef ZETA_CONFIG_DEBUG
			delete m_fpsCounter;
#endif
			delete graphics::Window::inst;
		}

		void Game::run(const std::string& initialLevel) {
			m_nextLevelName = initialLevel;
			m_level = new level::Level(initialLevel);

#ifdef ZETA_CONFIG_DEBUG
			FPSClock clock;
#endif
			Timer timer;
			unsigned long ticks = 0L;
			float elapsedTime = 0.f;
			float lastElapsedTime = 0.f;
			float levelStartTime = 0.f;
			level::GlobalData::inst->levelTicks = 0L;
			while (!graphics::Window::inst->shouldClose()) {

				elapsedTime = timer.elapsed();

				level::GlobalData::inst->level = m_level;
				level::GlobalData::inst->totalTime = elapsedTime;
				level::GlobalData::inst->deltaTime = elapsedTime - lastElapsedTime;
				level::GlobalData::inst->levelTime = elapsedTime - levelStartTime;

				// Level tick
				float ticksShouldHaveDone = elapsedTime * 60.f;
				while (ticks < ticksShouldHaveDone) {

					if (m_levelShouldChange) {
						// Notify all entities of level change?
						// Probably by an event
						delete m_level;

						levelStartTime = 0.f;
						level::GlobalData::inst->levelTicks = 0L;
						m_levelName = m_nextLevelName;

						m_level = new level::Level(m_nextLevelName);
						m_levelShouldChange = false;
					}

					input::InputInterface::inst->update();
					level::GlobalData::inst->totalTicks = ++ticks;
					++level::GlobalData::inst->levelTicks;
					m_level->tick();
				}

				graphics::Window::inst->drawStart();
				m_renderer->begin();
				m_renderer->setColour({ 1, 1, 1, 1 });
				m_level->render(*m_renderer);
#ifdef ZETA_CONFIG_DEBUG
				m_renderer->setColour({ 1, 1, 1, 0.5 });
				m_renderer->submit(m_fpsCounter);
#endif
				m_renderer->flushAll();
				graphics::Window::inst->drawEnd();

#ifdef ZETA_CONFIG_DEBUG
				clock.tick();
				std::string fps = std::to_string((int)clock.getFPS());
				while (fps.length() < 5) {
					fps = " " + fps;
				}
				m_fpsCounter->setString(fps + " FPS");
#endif

				lastElapsedTime = elapsedTime;
			}
		}
		
		void Game::changeLevel(const std::string& level) {
			
			m_levelShouldChange = true;
			m_nextLevelName = level;
		}

		void Game::registerBehaviours() {
			using namespace zeta;
			using namespace entity;
			ZETA_BEHAVIOUR_REGISTER(SpriteRenderBehaviour);
		}
	}
}