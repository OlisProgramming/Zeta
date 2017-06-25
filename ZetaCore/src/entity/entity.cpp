#include "entity.h"

#include "behaviour.h"
#include "../physics/aabb.h"

namespace zeta {
	namespace entity {

		using namespace physics;

		Entity::~Entity() {
			for (Behaviour* behaviour : m_behaviours)
				delete behaviour;
		}

		Behaviour* Entity::getBehaviour(const std::string& behaviourClassName) {
			for (Behaviour* behaviour : m_behaviours) {
				if (behaviour->getClassName() == behaviourClassName) {
					return behaviour;
				}
			}
			return nullptr;
		}

		void Entity::updatePhysObj() {
			if (!m_physObj) return;
			switch (m_physObj->getType()) {

			case PhysObjectType::AABB:
				static_cast<AABB*>(m_physObj)->set(getPos2(), getPos2() + getSize());
				break;
			}
		}

		void Entity:: preInit() { for (Behaviour* behaviour : m_behaviours) behaviour->preInit(); }
		void Entity::    init() { for (Behaviour* behaviour : m_behaviours) behaviour->init(); }
		void Entity::postInit() { for (Behaviour* behaviour : m_behaviours) behaviour->postInit(); }

		void Entity:: preTick() { for (Behaviour* behaviour : m_behaviours) behaviour->preTick(); }
		void Entity::    tick() { for (Behaviour* behaviour : m_behaviours) behaviour->tick(); }
		void Entity::postTick() { for (Behaviour* behaviour : m_behaviours) behaviour->postTick(); }

		void Entity:: preRender(graphics::Renderer& renderer) { for (Behaviour* behaviour : m_behaviours) behaviour->preRender(renderer); }
		void Entity::    render(graphics::Renderer& renderer) { for (Behaviour* behaviour : m_behaviours) behaviour->render(renderer); }
		void Entity::postRender(graphics::Renderer& renderer) { for (Behaviour* behaviour : m_behaviours) behaviour->postRender(renderer); }
	}
}