#include "renderable.h"

namespace zeta {
	namespace graphics {

		Renderable::Renderable(glm::vec3 pos, glm::vec2 size) :
			m_pos(pos), m_size(size), m_tex(nullptr), m_rot(0.f), m_scale(1, 1), m_pivot(0, 0), m_isTranslucent(false) {
		}
	}
}