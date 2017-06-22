#include "line.h"

namespace zeta {
	namespace graphics {

		Line::Line(glm::vec2& a, glm::vec2& b, float z, float width) :
			Sprite(glm::vec3((a+b)*0.5f, z), glm::vec2(1, 1), false) {
			centrePivot();
			float w = a.x - b.x;
			float h = a.y - b.y;
			setRot(-atan(w / h));
			setScale(glm::vec2(width, glm::length(a - b)));
		}

		void Line::update(glm::vec2& a, glm::vec2& b, float z, float width) {
			setPos(glm::vec3((a + b)*0.5f, z));
			setScale(glm::vec2(width, glm::length(a - b)));
			centrePivot();
			float w = a.x - b.x;
			float h = a.y - b.y;
			setRot(-atan(w / h));
		}
	}
}