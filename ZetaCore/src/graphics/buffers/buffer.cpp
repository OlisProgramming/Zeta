#include "buffer.h"

namespace zeta {
	namespace graphics {

		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint elementCount) :
			m_elementCount(elementCount) {

			glGenBuffers(1, &m_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Buffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}

		void Buffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}