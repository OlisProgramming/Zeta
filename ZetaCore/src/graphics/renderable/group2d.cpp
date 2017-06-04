#include "group2d.h"

#include <glm\gtc\matrix_transform.hpp>

namespace zeta {
	namespace graphics {

		Group2D::Group2D(glm::mat4 transformation) :
			Renderable2D(glm::vec3(), glm::vec2()), m_transformation(transformation) {
		}

		Group2D::Group2D(glm::vec3 translation) :
			Group2D(glm::translate(glm::mat4(), translation)) {
		}

		Group2D::~Group2D() {
			for (Renderable2D* renderable : m_renderables)
				delete renderable;
		}

		void Group2D::submit(Renderable2D* renderable) {
			m_renderables.push_back(renderable);
		}
	}
}