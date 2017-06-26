#pragma once

#include "behaviour.h"
#include "../graphics/renderable/sprite.h"

namespace zeta {
	namespace entity {

		class SpriteRenderBehaviour : public Behaviour {

		private:
			Sprite* m_sprite;

		public:
			ZETA_BEHAVIOUR_CLASS_BODY(SpriteRenderBehaviour)

			SpriteRenderBehaviour(Entity* parent, const std::string& spriteFname, bool isTranslucent = false);
			virtual ~SpriteRenderBehaviour();
			void render(Renderer& renderer) override;
		};
	}
}