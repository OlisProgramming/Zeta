#include "entity.h"

#include "behaviour.h"

namespace zeta {
	namespace entity {

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