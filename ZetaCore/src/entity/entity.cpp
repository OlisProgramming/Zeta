#include "entity.h"

#include "behaviour.h"

namespace zeta {
	namespace entity {

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