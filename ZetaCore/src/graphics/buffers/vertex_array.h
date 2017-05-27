#pragma once

#include <GL\glew.h>
#include <vector>

#include "buffer.h"

namespace zeta {
	namespace graphics {

		class VertexArray {

		private:
			GLuint m_id;
			std::vector<Buffer*> m_buffers;

		public:
			VertexArray();
			~VertexArray();
			
			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}
