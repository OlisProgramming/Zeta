#include "sprite_render_behaviour.h"
#include "entity.h"

namespace zeta {
	namespace entity {

		SpriteRenderBehaviour* SpriteRenderBehaviour::generate(Entity* parent, const std::vector<std::string>& params) {
			if (params.size() > 1)
				return new SpriteRenderBehaviour(parent, params[0], util::isTruthy(params[1]));
			else
				return new SpriteRenderBehaviour(parent, params[0], false);
		}

		SpriteRenderBehaviour::SpriteRenderBehaviour(Entity* parent, const std::string& spriteFname, bool isTranslucent) :
			Behaviour(parent) {

			m_sprite = new Sprite(m_parent->getPos(), spriteFname, isTranslucent);
		}

		void SpriteRenderBehaviour::render(Renderer& renderer) {
			renderer.submit(m_sprite);
		}
	}
}