#pragma once

#include <glm\glm.hpp>

namespace zeta {
	namespace physics {

		class AABB;

		enum class PhysObjectType {
			AABB
		};

		class PhysObject {

		public:
			bool collide(const PhysObject& other) const;
			bool collide(const glm::vec2& other) const;
			virtual const PhysObjectType getType() const = 0;

			static bool collide(const PhysObject& a, const PhysObject& b);
			static bool collide(const glm::vec2& a, const PhysObject& b);
			inline static bool collide(const PhysObject& a, const glm::vec2& b) { return collide(b, a); }

			static bool collide_AABB_AABB(const AABB& a, const AABB& b);
			static bool collide_Point_AABB(const glm::vec2& a, const AABB& b);
		};
	}
}