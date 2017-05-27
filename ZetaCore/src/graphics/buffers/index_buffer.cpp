#pragma once

#include "index_buffer.h"

namespace zeta {
	namespace graphics {

		IndexBuffer::IndexBuffer(GLushort* data, GLsizei count) :
			m_count(count) {

			glGenBuffers(1, &m_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}

		void IndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}