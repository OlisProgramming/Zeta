#include "physics_aabb_behaviour.h"

#include "entity.h"

namespace zeta {
	namespace entity {

		PhysicsAABBBehaviour* PhysicsAABBBehaviour::generate(Entity* parent, const std::vector<std::string>& params) {
			return new PhysicsAABBBehaviour(parent);
		}

		PhysicsAABBBehaviour::PhysicsAABBBehaviour(Entity* parent) :
			Behaviour(parent), m_aabb(glm::vec2(parent->getPos()), glm::vec2(parent->getPos()) + parent->getSize()) {
		}

		PhysicsAABBBehaviour::PhysicsAABBBehaviour(Entity* parent, glm::vec2 pos, glm::vec2 size) :
			Behaviour(parent), m_aabb(pos, pos + size) {
		}

		void PhysicsAABBBehaviour::tick() {
			m_aabb = physics::AABB(glm::vec2(m_parent->getPos()), glm::vec2(m_parent->getPos()) + m_parent->getSize());
		}
	}
}