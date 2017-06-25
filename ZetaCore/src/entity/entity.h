#pragma once

#include <glm\glm.hpp>
#include <vector>
#include "../graphics/renderer/renderer.h"
#include "../physics/phys_object.h"

namespace zeta {
	namespace entity {

		class Behaviour;

		class Entity {

		private:
			glm::vec3 m_pos;
			glm::vec2 m_size;
			physics::PhysObject* m_physObj;
			std::vector<Behaviour*> m_behaviours;

		public:
			Entity(glm::vec3 pos, glm::vec2 size) : m_pos(pos), m_size(size), m_physObj(nullptr) {}
			~Entity();
			inline const std::vector<Behaviour*>& getAllBehaviours() { return m_behaviours; }
			inline void addBehaviour(Behaviour* behaviour) { m_behaviours.push_back(behaviour); }
			// Avoid this function. Use ZETA_ENTITY_GET_BEHAVIOUR instead as it also inserts a static_cast and produces compile-time errors on spelling mistakes.
			Behaviour* getBehaviour(const std::string& behaviourClassName);
			inline const glm::vec3& getPos() const { return m_pos; }
			inline glm::vec2 getPos2() const { return m_pos; }
			inline void setPos(glm::vec3& pos) { m_pos = pos; updatePhysObj(); }
			inline void setPos(glm::vec2& pos) { m_pos.x = pos.x; m_pos.y = pos.y; updatePhysObj(); }
			inline const glm::vec2& getSize() const { return m_size; }
			inline void setSize(glm::vec2& size) { m_size = size; }
			inline const physics::PhysObject* getPhysObj() { return m_physObj; }
			inline void setPhysObj(physics::PhysObject* obj) {
				if (m_physObj == nullptr) delete m_physObj;
				m_physObj = obj;
			}
			virtual void updatePhysObj();

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