#include "renderable2d.h"

namespace zeta {
	namespace graphics {

		Renderable2D::Renderable2D(glm::vec3 pos, glm::vec2 size) :
			m_pos(pos), m_size(size), m_tex(nullptr) {
		}
	}
}