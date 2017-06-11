#include "renderable.h"

namespace zeta {
	namespace graphics {

		Renderable::Renderable(glm::vec3 pos, glm::vec2 size) :
			m_pos(pos), m_size(size), m_tex(nullptr) {
		}
	}
}