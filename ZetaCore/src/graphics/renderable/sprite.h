#pragma once

#include "renderable2d.h"
#include "../texture/texture_manager.h"

namespace zeta {
	namespace graphics {

		class Sprite : public Renderable2D {

		public:
			Sprite(glm::vec3 pos, glm::vec2 size, bool isTranslucent);
			Sprite(glm::vec3 pos, glm::vec2 size, Texture* tex, glm::vec2 uvStart, glm::vec2 uvEnd, bool isTranslucent);
			Sprite(glm::vec3 pos, glm::vec2 size, const std::string& texture, bool isTranslucent);
			inline RenderableType getType() const override { return RenderableType::SPRITE; }
		};
	}
}