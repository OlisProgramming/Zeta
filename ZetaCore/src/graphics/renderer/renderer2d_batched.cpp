#include "renderer2d_batched.h"

namespace zeta {
	namespace graphics {

		IndexBuffer* Renderer2DBatched::m_ibo;

		Renderer2DBatched::Renderer2DBatched(Shader& shader) :
			Renderer2D(shader) {
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);
			
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::pos));
			
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		Renderer2DBatched::~Renderer2DBatched() {
			glDeleteBuffers(1, &m_vbo);
		}

		void Renderer2DBatched::init() {
			// Generate indices

			GLushort indices[RENDERER_INDICES_SIZE];
			int offset = 0;
			for (unsigned int i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
				indices[i + 0] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;
				offset += 4;
			}
			m_ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
		}

		void Renderer2DBatched::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			m_vertexbuf = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));;
		}

		void Renderer2DBatched::submit(Renderable2D* renderable) {

			if (m_indexcount + 6 >= RENDERER_INDICES_SIZE) {
				flush();
				begin();
			}

			glm::vec3 pos = renderable->getPos();
			glm::vec2 size = renderable->getSize();

			m_vertexbuf->pos = pos; // glm::vec3(pos.x, pos.y, pos.z);
			++m_vertexbuf;
			m_vertexbuf->pos = glm::vec3(pos.x+size.x, pos.y, pos.z);
			++m_vertexbuf;
			m_vertexbuf->pos = glm::vec3(pos.x+size.x, pos.y+size.y, pos.z);
			++m_vertexbuf;
			m_vertexbuf->pos = glm::vec3(pos.x, pos.y+size.y, pos.z);
			++m_vertexbuf;

			m_indexcount += 6;
		}

		void Renderer2DBatched::flush() {
			// End batch
			
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Flush

			glBindVertexArray(m_vao);
			m_ibo->bind();
			glDrawElements(GL_TRIANGLES, m_indexcount, GL_UNSIGNED_SHORT, 0);
			m_ibo->unbind();
			glBindVertexArray(0);

			m_indexcount = 0;
		}
	}
}
