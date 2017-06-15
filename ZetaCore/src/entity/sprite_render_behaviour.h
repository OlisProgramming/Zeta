#pragma once

#include "behaviour.h"
#include "../graphics/renderable/sprite.h"

namespace zeta {
	namespace entity {

		class SpriteRenderBehaviour : public Behaviour {

		private:
			Sprite* m_sprite;

		public:
			static SpriteRenderBehaviour* generate(Entity* parent, const std::vector<std::string>& params);
			SpriteRenderBehaviour(Entity* parent, const std::string& spriteFname, bool isTranslucent = false);
			void render(Renderer& renderer) override;
		};
	}
}