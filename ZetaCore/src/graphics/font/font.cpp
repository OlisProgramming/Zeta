#include "font.h"

#include "../../util/logging.h"

namespace zeta {
	namespace graphics {

		Font::Font(const std::string& fname, unsigned int size) :
			m_fname(fname), m_size(size) {

			ZLog("Loading font from file " + fname + " of size " + std::to_string(size));

			m_texatlas = ftgl::texture_atlas_new(512, 512, 1);
			std::string fullFname = "../res/fonts/" + fname;
			m_font = ftgl::texture_font_new_from_file(m_texatlas, (float)size, fullFname.c_str());

			/*for (char a = 32; a < 126; ++a)  // Pre-initialise font data.
				ftgl::texture_font_get_glyph(m_font, a);*/

			ZLog("Font loaded");
		}
	}
}