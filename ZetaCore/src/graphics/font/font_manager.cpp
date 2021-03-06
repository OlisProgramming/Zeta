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

			if (!fnt) {
				fnt = new Font(fname, size);
			}

			return fnt;
		}

		void FontManager::cleanup() {
			for (Font* font : m_fonts) {
				delete font;
			}
		}

		float FontManager::getTextWidth(Font* fnt, std::string text, bool includeEndSpace) {

			float width = 0.f;

			if (includeEndSpace) {

				for (unsigned int i = 0; i < text.length(); ++i) {
					ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(fnt->getFTGLFont(), text[i]);
					width += glyph->advance_x;
				}
			}
			else {

				for (unsigned int i = 0; i < text.length() - 1; ++i) {
					ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(fnt->getFTGLFont(), text[i]);
					width += glyph->advance_x;
				}
				ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(fnt->getFTGLFont(), text[text.length() - 1]);
				width += glyph->width;
			}

			return width;
		}
	}
}