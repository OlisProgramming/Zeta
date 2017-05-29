#include "sprite.h"

namespace zeta {
	namespace graphics {

		Sprite::Sprite(glm::vec3 pos, glm::vec2 size) :
			Renderable2D(pos, size) {
		}
	}
}