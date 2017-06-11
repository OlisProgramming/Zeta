#include "label.h"

namespace zeta {
	namespace graphics {

		Label::Label(std::string string, glm::vec3 pos, bool isTranslucent) :
			Renderable(pos, glm::vec2()), m_string(string) {
			m_isTranslucent = isTranslucent;
		}
	}
}