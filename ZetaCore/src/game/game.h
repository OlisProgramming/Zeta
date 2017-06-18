#pragma once

#include "../graphics/window.h"
#include "../graphics/renderable/label.h"
#include "../graphics/renderer/renderer.h"
#include "../graphics/renderer/camera.h"
#include "../level/level.h"

namespace zeta {
	namespace game {

		class Game {

		public:
			static Game* inst;
		private:
			graphics::Shader* m_shader;
			graphics::Renderer* m_renderer;
			graphics::Camera* m_camera;
			level::Level* m_level;
#ifdef ZETA_CONFIG_DEBUG
			graphics::Label* m_fpsCounter;
#endif

		public:
			Game(const std::string& name, int width, int height);
			~Game();
			void run(const std::string& initialLevel);
			void changeLevel(const std::string& level);
		private:
			void registerBehaviours();
		};
	}
}