#pragma once

#include <GL\glew.h>
#include <string>

namespace zeta {
	namespace graphics {

		class Texture {

		private:
			//std::string m_fname;
			GLuint m_id;
			unsigned int m_width, m_height;

		public:
			Texture(std::string path);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth()  const { return m_width;  }
			inline const unsigned int getHeight() const { return m_height; }
			inline const GLuint getTexID() const { return m_id; }
		};
	}
}