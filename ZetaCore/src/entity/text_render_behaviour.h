#pragma once

#include "behaviour.h"
#include "../graphics/renderable/label.h"

namespace zeta {
	namespace entity {

		class TextRenderBehaviour : public Behaviour {

		private:
			Label* m_label;

		public:
			ZETA_BEHAVIOUR_CLASS_BODY(TextRenderBehaviour)

			TextRenderBehaviour(Entity* parent, const std::string& text, const std::string& font, unsigned int fontSize, bool isTranslucent = false);
			~TextRenderBehaviour();
			void render(Renderer& renderer) override;
		};
	}
}