#include "vertex_array.h"

namespace zeta {
	namespace graphics {

		VertexArray::VertexArray() {
			glGenVertexArrays(1, &m_id);
		}

		VertexArray::~VertexArray() {
			for (Buffer* buffer : m_buffers) {
				delete buffer;
			}
			glDeleteVertexArrays(1, &m_id);
		}

		void VertexArray::addBuffer(Buffer* buffer, GLuint index) {
			bind();
			buffer->bind();
			
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getElementCount(), GL_FLOAT, GL_FALSE, 0, NULL);
			m_buffers.push_back(buffer);

			buffer->unbind();
			unbind();
		}

		void VertexArray::bind() const {
			glBindVertexArray(m_id);
		}

		void VertexArray::unbind() const {
			glBindVertexArray(0);
		}
	}
}