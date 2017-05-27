#pragma once

#include <GL\glew.h>

namespace zeta {
	namespace graphics {

		class IndexBuffer {

		private:
			GLuint m_id;
			GLuint m_count;

		public:
			IndexBuffer(GLushort* data, GLsizei count);

			void bind() const;
			void unbind() const;
			inline GLuint getCount() const { return m_count; }
		};
	}
}