#include "font_manager.h"

namespace zeta {
	namespace graphics {

		FontManager* FontManager::inst;

		FontManager::FontManager() {
			inst = this;
		}

		void FontManager::add(Font* font) {
			m_fonts.push_back(font);
		}

		Font* FontManager::get(const std::string& fname, unsigned int size) {
			Font* fnt = nullptr;
			for (Font* guess : m_fonts) {
				if (guess->getFname() == fname && guess->getSize() == size) {
					fnt = guess;
					break;
				}
			}

			return fnt;
		}

		void FontManager::cleanup() {
			for (Font* font : m_fonts) {
				delete font;
			}
		}
	}
}