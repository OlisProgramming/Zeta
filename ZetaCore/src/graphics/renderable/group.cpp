#include "group.h"

#include <glm\gtc\matrix_transform.hpp>

namespace zeta {
	namespace graphics {

		Group::Group(glm::mat4 transformation) :
			Renderable(glm::vec3(), glm::vec2()), m_transformation(transformation) {
		}

		Group::Group(glm::vec3 translation) :
			Group(glm::translate(glm::mat4(), translation)) {
		}

		Group::~Group() {
			for (Renderable* renderable : m_renderables)
				delete renderable;
		}

		void Group::submit(Renderable* renderable) {
			m_renderables.push_back(renderable);
		}
	}
}