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
			inline const std::vector<Behaviour*>& getAllBehaviours() { return m_behaviours; }
			inline void addBehaviour(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }
			// Avoid this function. Use ZETA_ENTITY_GET_BEHAVIOUR instead as it also inserts a static_cast and produces compile-time errors on spelling mistakes.
			Behaviour* getBehaviour(const std::string& behaviourClassName);
			inline const glm::vec3& getPos() const { return m_pos; }

#define ZETA_ENTITY_GET_BEHAVIOUR(ent, behaviourClassName) (static_cast<behaviourClassName*>(ent->getBehaviour(#behaviourClassName)))

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