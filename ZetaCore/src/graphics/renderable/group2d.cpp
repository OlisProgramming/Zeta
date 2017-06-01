#include "group2d.h"

namespace zeta {
	namespace graphics {

		Group2D::Group2D(glm::mat4 transformation) :
			Renderable2D(glm::vec3(), glm::vec2()), m_transformation(transformation) {
		}

		void Group2D::submit(Renderable2D* renderable) {
			m_renderables.push_back(renderable);
		}
	}
}