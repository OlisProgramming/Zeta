#include "aabb.h"

namespace zeta {
	namespace physics {

		AABB::AABB(glm::vec2& a, glm::vec2& b) {
			if (a.x < b.x) {
				if (a.y < b.y) {
					m_low = { a.x, a.y };
					m_high = { b.x, b.y };
				} else {
					m_low = { a.x, b.y };
					m_high = { b.x, a.y };
				}
			}
			else {
				if (a.y < b.y) {
					m_low = { b.x, a.y };
					m_high = { a.x, b.y };
				}
				else {
					m_low = { b.x, b.y };
					m_high = { a.x, a.y };
				}
			}
		}
	}
}