#include "sprite.h"

namespace zeta {
	namespace graphics {

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size) :
			Renderable2D(pos, size) {
		}

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size, Texture* tex) :
			Renderable2D(pos, size) {
			m_tex = tex;
		}
	}
}