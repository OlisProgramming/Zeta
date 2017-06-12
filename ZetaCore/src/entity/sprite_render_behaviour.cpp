#include "sprite_render_behaviour.h"
#include "entity.h"

namespace zeta {
	namespace entity {

		SpriteRenderBehaviour::SpriteRenderBehaviour(Entity* parent, const std::string& spriteFname, bool isTranslucent) :
			Behaviour(parent) {

			m_sprite = new Sprite(m_parent->getPos(), spriteFname, isTranslucent);
		}

		void SpriteRenderBehaviour::render(Renderer& renderer) {
			renderer.submit(m_sprite);
		}
	}
}