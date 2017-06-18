#include "texture.h"

#include "../../util/image_load.h"
#include "../../util/fileutils.h"

namespace zeta {
	namespace graphics {

		Texture::Texture(std::string path) {

			if (!util::fileExists(path)) {
				throw std::runtime_error("Texture file " + path + " does not exist!");
			}

			FIBITMAP* dib;
			util::IMAGE_DATA pixels = util::loadImage(path.c_str(), m_width, m_height, &dib);
			//printf("Texture dimensions: %dx%d\n", m_width, m_height);

			puts("create tex");

			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			// Only works with 32-bit RGBA files at the moment (not sure how to tell the image format, this is the type outputted by TexturePacker)
			// Just gives weird values (and OpenGL Error 1281) when file does not exist - it doesn't crash

			FreeImage_Unload(dib);
		}	

		Texture::~Texture() {
			glDeleteTextures(1, &m_id);
		}

		void Texture::bind() const {
			glBindTexture(GL_TEXTURE_2D, m_id);
		}

		void Texture::unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}