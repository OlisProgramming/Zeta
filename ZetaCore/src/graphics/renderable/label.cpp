#include "label.h"

namespace zeta {
	namespace graphics {

		Label::Label(std::string string, glm::vec3 pos) :
			Renderable2D(pos, glm::vec2()), m_string(string) {
		}
	}
}