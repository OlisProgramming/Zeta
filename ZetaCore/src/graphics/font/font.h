#pragma once

#include <string>
#include <freetype-gl.h>

namespace zeta {
	namespace graphics {

		class Font {

		private:
			ftgl::texture_atlas_t* m_texatlas;
			ftgl::texture_font_t* m_font;
			std::string m_fname;
			unsigned int m_size;

		public:
			Font(std::string fname, unsigned int size);

			inline const std::string& getFname() const { return m_fname; }
			inline const unsigned int getSize() const { return m_size; }
			inline ftgl::texture_atlas_t* getTextureAtlas() const { return m_texatlas; }
			inline ftgl::texture_font_t* getFTGLFont() const { return m_font; }
		};
	}
}