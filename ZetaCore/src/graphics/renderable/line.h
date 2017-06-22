#pragma once

#include "sprite.h"

namespace zeta {
	namespace graphics {

		class Line : public Sprite {

		public:
			Line(glm::vec2& a, glm::vec2& b, float z, float width);
			void update(glm::vec2& a, glm::vec2& b, float z, float width);
		};
	}
}