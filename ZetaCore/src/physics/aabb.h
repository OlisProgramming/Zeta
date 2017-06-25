#pragma once

#include <glm\glm.hpp>
#include "phys_object.h"

namespace zeta {
	namespace physics {

		class AABB : public PhysObject {

		public:
			glm::vec2 m_low, m_high;
			AABB() {}
			AABB(const glm::vec2& a, const glm::vec2& b);
			inline const PhysObjectType getType() const override { return PhysObjectType::AABB; }

			void set(const glm::vec2& a, const glm::vec2& b);
			inline const glm::vec2& low() const { return m_low; }
			inline const glm::vec2& high() const { return m_high; }
		};
	}
}