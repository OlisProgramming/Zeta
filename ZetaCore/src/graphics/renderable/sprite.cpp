#include "sprite.h"

namespace zeta {
	namespace graphics {

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size, bool isTranslucent) :
			Renderable2D(pos, size) {
			m_isTranslucent = isTranslucent;
		}

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size, Texture* tex, bool isTranslucent) :
			Renderable2D(pos, size) {
			m_tex = tex;
			m_isTranslucent = isTranslucent;
		}
	}
}