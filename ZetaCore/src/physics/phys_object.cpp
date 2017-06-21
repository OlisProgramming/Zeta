#include "phys_object.h"

#include "aabb.h"

namespace zeta {
	namespace physics {

		bool PhysObject::collide(const PhysObject& other) const {
			return collide(*this, other);
		}

		bool PhysObject::collide(const PhysObject& a, const PhysObject& b) {
			switch (a.getType()) {
			case PhysObjectType::AABB:
				switch (b.getType()) {
				case PhysObjectType::AABB:
					return collide((AABB&)a, (AABB&)b);
				}
				break;
			}
			return false;  // should never get here
		}

		bool PhysObject::collide(const AABB& a, const AABB& b) {
			
			if (a.high().x <= b.low().x) return false;
			if (b.high().x <= a.low().x) return false;
			if (a.high().y <= b.low().y) return false;
			if (b.high().y <= a.low().y) return false;

			return true;
		}
	}
}