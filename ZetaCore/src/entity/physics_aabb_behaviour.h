#pragma once

#include "behaviour.h"
#include "../physics/aabb.h"

namespace zeta {
	namespace entity {

		class PhysicsAABBBehaviour : public Behaviour {

			ZETA_BEHAVIOUR_CLASS_BODY(PhysicsAABBBehaviour)

		private:
			physics::AABB m_aabb;
		public:
			PhysicsAABBBehaviour(Entity* parent);
			PhysicsAABBBehaviour(Entity* parent, glm::vec2 pos, glm::vec2 size);

			void tick() override;

			inline physics::AABB& getAABB() { return m_aabb; }
		};
	}
}