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
		};
	}
}