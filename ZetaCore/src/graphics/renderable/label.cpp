#include "label.h"
#include "../font/font_manager.h"
#include "../renderer/renderer.h"

namespace zeta {
	namespace graphics {

		Label::Label(std::string string, glm::vec3 pos, const std::string& font, unsigned int fontSize, bool isTranslucent) :
			Renderable(pos, glm::vec2()), m_string(string) {
			m_font = FontManager::inst->get(font, fontSize);
			m_isTranslucent = isTranslucent;
		}

		void Label::centreHoriz(Font* fnt) {
			setPivotX(FontManager::inst->getTextWidth(fnt, m_string) / 2.f);
		}

		void Label::centreHoriz(const std::string& fontFname, unsigned int size) {
			Font* fnt = FontManager::inst->get(fontFname, size);
			if (fnt) centreHoriz(fnt);
		}

		void Label::centreHoriz(Renderer& renderer) {
			setPivotX(FontManager::inst->getTextWidth(renderer.getFont(), m_string) / 2.f);
		}
	}
}