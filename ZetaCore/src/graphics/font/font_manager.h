#pragma once

#include <vector>
#include "font.h"

namespace zeta {
	namespace graphics {

		class FontManager {

		private:
			std::vector<Font*> m_fonts;

		public:
			static FontManager* inst;

		public:
			FontManager();
			inline void add(const std::string& fname, unsigned int size) { add(new Font(fname, size)); }
			void add(Font* font);
			Font* get(const std::string& fname, unsigned int size);
			void cleanup();

			float getTextWidth(Font* fnt, std::string text, bool includeEndSpace = false);
			inline float getTextWidth(const std::string& fontFname, unsigned int size, std::string text, bool includeEndSpace = false) {
				Font* fnt = get(fontFname, size);
				if (!fnt) return 0.0f;
				//printf("%d\n", (int)includeEndSpace);
				return getTextWidth(fnt, text, includeEndSpace);
			}
		};
	}
}