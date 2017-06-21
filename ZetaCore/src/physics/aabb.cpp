#include "aabb.h"

namespace zeta {
	namespace physics {

		AABB::AABB(const glm::vec2& a, const glm::vec2& b) {
			set(a, b);
		}

		void AABB::set(const glm::vec2& a, const glm::vec2& b) {
			if (a.x < b.x) {
				if (a.y < b.y) {
					m_low = { a.x, a.y };
					m_high = { b.x, b.y };
				}
				else {
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