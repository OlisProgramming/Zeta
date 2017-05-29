#pragma once

#include "renderable2d.h"

namespace zeta {
	namespace graphics {

		class Sprite : public Renderable2D {

		public:
			Sprite(glm::vec3 pos, glm::vec2 size);
		};
	}
}