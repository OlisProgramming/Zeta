#pragma once

#include <GL\glew.h>

namespace zeta {
	namespace graphics {
		
		class Buffer {
		
		private:
			GLuint m_id;
			GLuint m_elementCount;  // how many elements in one datum (eg 3 for vec3)

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint elementCount);
			~Buffer();

			void bind() const;
			void unbind() const;
			inline GLuint getElementCount() const { return m_elementCount; }
		};
	}
}