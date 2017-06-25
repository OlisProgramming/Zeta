#include "phys_object.h"

#include "aabb.h"

namespace zeta {
	namespace physics {

		bool PhysObject::collide(const PhysObject& other) const {
			return collide(*this, other);
		}

		bool PhysObject::collide(const glm::vec2& other) const {
			return collide(*this, other);
		}

		bool PhysObject::collide(const PhysObject& a, const PhysObject& b) {
			switch (a.getType()) {
			case PhysObjectType::AABB:
				switch (b.getType()) {
				case PhysObjectType::AABB:
					return collide_AABB_AABB((AABB&)a, (AABB&)b);
				}
				break;
			}
			return false;  // should never get here
		}

		bool PhysObject::collide(const glm::vec2& a, const PhysObject& b) {
			switch (b.getType()) {
			case PhysObjectType::AABB:
				return collide_Point_AABB(a, (AABB&)b);
				break;
			}
			return false;  // should never get here
		}

		bool PhysObject::collide_AABB_AABB(const AABB& a, const AABB& b) {
			
			if (a.high().x <= b.low().x) return false;
			if (b.high().x <= a.low().x) return false;
			if (a.high().y <= b.low().y) return false;
			if (b.high().y <= a.low().y) return false;

			return true;
		}

		bool PhysObject::collide_Point_AABB(const glm::vec2& a, const AABB& b) {
			
			if (a.x <= b.low().x) return false;
			if (a.x >= b.high().x) return false;
			if (a.y <= b.low().y) return false;
			if (a.y >= b.high().y) return false;

			return true;
		}
	}
}