#pragma once

#include <glm\glm.hpp>
#include <vector>
#include "../graphics/renderer/renderer.h"

namespace zeta {
	namespace entity {

		class Behaviour;

		class Entity {

		private:
			glm::vec3 m_pos;
			std::vector<Behaviour*> m_behaviours;

		public:
			Entity(glm::vec3 pos) : m_pos(pos) {}
			inline void addBehaviour(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }
			inline const glm::vec3& getPos() const { return m_pos; }

			void  preInit();
			void     init();
			void postInit();
			
			void  preTick();
			void     tick();
			void postTick();
			
			void  preRender(graphics::Renderer& renderer);
			void     render(graphics::Renderer& renderer);
			void postRender(graphics::Renderer& renderer);
		};
	}
}