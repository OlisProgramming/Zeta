#include "text_render_behaviour.h"

#include "entity.h"

namespace zeta {
	namespace entity {
		TextRenderBehaviour::TextRenderBehaviour(Entity* parent, const std::string& text, const std::string& font, unsigned int fontSize, bool isTranslucent) :
			Behaviour(parent) {

			m_label = new Label(text, parent->getPos(), font, fontSize, isTranslucent);
		}

		TextRenderBehaviour::~TextRenderBehaviour() {
			delete m_label;
		}

		void TextRenderBehaviour::render(Renderer& renderer) {
			m_label->setPos(m_parent->getPos());
			renderer.submit(m_label);
		}
	}
}