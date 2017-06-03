#include "renderer2d_batched.h"
#include "../renderable/group2d.h"

namespace zeta {
	namespace graphics {

		IndexBuffer* Renderer2DBatched::m_ibo;

		Renderer2DBatched::Renderer2DBatched(Shader* shader) :
			Renderer2D(shader) {
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);
			
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
			glEnableVertexAttribArray(SHADER_TEXID_INDEX);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::pos));
			glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texCoord));
			glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texID));
			
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

			if (renderable->getType() == RenderableType::GROUP) {
				m_transformStack.push((static_cast<Group2D*>(renderable))->getMatrix(), false);
				for (Renderable2D* child : (static_cast<Group2D*>(renderable))->getChildren())
					submit(child);
				m_transformStack.pop();
				return;
			}

			if (m_indexcount + 6 >= RENDERER_INDICES_SIZE) {
				flush();
				begin();
			}

			glm::vec3 pos = renderable->getPos();
			glm::vec2 size = renderable->getSize();
			GLuint texid = renderable->getTexID();

			float textureSlot = 0.0f;
			if (texid > 0) {
				bool found = false;
				for (unsigned int i = 0; i < m_textureSlots.size(); ++i) {
					if (m_textureSlots[i] == texid) {
						found = true;
						textureSlot = (float)(i + 1);
						break;
					}
				}

				if (!found) {
					if (m_textureSlots.size() >= 32) {
						flush();
						begin();
					}
					m_textureSlots.push_back(texid);
					textureSlot = (float)(m_textureSlots.size());
				}
			}

			m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(pos, 1.0);
			m_vertexbuf->texCoord = glm::vec2(0, 0);
			m_vertexbuf->texID = textureSlot;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(pos.x+size.x, pos.y, pos.z, 1.0);
			m_vertexbuf->texCoord = glm::vec2(1, 0);
			m_vertexbuf->texID = textureSlot;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(pos.x+size.x, pos.y+size.y, pos.z, 1.0);
			m_vertexbuf->texCoord = glm::vec2(1, 1);
			m_vertexbuf->texID = textureSlot;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(pos.x, pos.y+size.y, pos.z, 1.0);
			m_vertexbuf->texCoord = glm::vec2(0, 1);
			m_vertexbuf->texID = textureSlot;
			++m_vertexbuf;

			m_indexcount += 6;
		}

		void Renderer2DBatched::flush() {
			// End batch
			
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Flush

			for (unsigned int i = 0; i < m_textureSlots.size(); ++i) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}

			glBindVertexArray(m_vao);
			m_ibo->bind();
			glDrawElements(GL_TRIANGLES, m_indexcount, GL_UNSIGNED_SHORT, 0);
			m_ibo->unbind();
			glBindVertexArray(0);

			m_indexcount = 0;
		}
	}
}
