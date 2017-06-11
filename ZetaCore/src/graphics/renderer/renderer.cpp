#include "renderer.h"
#include "../renderable/group.h"
#include "../renderable/label.h"

namespace zeta {
	namespace graphics {

		IndexBuffer* Renderer::m_ibo;

		Renderer::Renderer(Shader* shader) :
			m_shader(shader) {
			glGenVertexArrays(1, &m_vao);
			glGenBuffers(1, &m_vbo);
			
			glBindVertexArray(m_vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
			glEnableVertexAttribArray(SHADER_TEXID_INDEX);
			glEnableVertexAttribArray(SHADER_COL_INDEX);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::pos));
			glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texCoord));
			glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::texID));
			glVertexAttribPointer(SHADER_COL_INDEX, 4, GL_UNSIGNED_BYTE, GL_FALSE,
				RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::col));
			
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			m_font = m_defaultfont = new Font("consola.ttf", 15);

			setColour({1, 1, 1, 1});

			m_translucentRenderableList = nullptr;
		}

		Renderer::~Renderer() {
			glDeleteBuffers(1, &m_vbo);
			delete m_shader;
		}

		void Renderer::init() {
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

		void Renderer::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			m_vertexbuf = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

			m_textureSlots.clear();
			m_textureSlots.push_back(m_font->getTextureAtlas()->id);  // Force font texture to occupy sampler location 0.
		}

		void Renderer::submit(Renderable* renderable) {
			submit(renderable, false);
		}

		void Renderer::submit(Renderable* renderable, bool renderTranslucentImmediately) {

			if (renderable->isTranslucent() && !renderTranslucentImmediately) {
				queueTranslucentRenderable(renderable);
				return;
			}

			if (renderable->getType() == RenderableType::GROUP) {
				m_transformStack.push((static_cast<Group*>(renderable))->getMatrix(), false);
				for (Renderable* child : (static_cast<Group*>(renderable))->getChildren())
					submit(child);
				m_transformStack.pop();
				return;
			}
			else if (renderable->getType() == RenderableType::LABEL) {
				Label* label = static_cast<Label*>(renderable);
				glm::mat4& mat = label->getTransformationMatrix();
				
				// DRAW STRING
				float textureSlot = 0.0f;
				bool found = false;
				for (unsigned int i = 0; i < m_textureSlots.size(); ++i) {
					if (m_textureSlots[i] == m_font->getTextureAtlas()->id) {
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
					m_textureSlots.push_back(m_font->getTextureAtlas()->id);
					textureSlot = (float)(m_textureSlots.size());
				}

				glm::vec2 size(512, 512);
				std::string s = label->getString();

				if (m_indexcount + 6 * s.length() >= RENDERER_INDICES_SIZE) {
					flush();
					begin();
				}

				float offset = 0.0f;

				for (unsigned int i = 0; i < s.length(); ++i) {

					char c = s[i];
					ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(m_font->getFTGLFont(), c);
					if (glyph != NULL) {

						float x0 = glyph->offset_x + offset;
						float y0 = -glyph->offset_y;
						float x1 = x0 + glyph->width;
						float y1 = y0 + glyph->height;

						float s0 = glyph->s0;
						float t0 = glyph->t0;
						float s1 = glyph->s1;
						float t1 = glyph->t1;

						offset += glyph->advance_x;

						m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(x0, y0, 0.0f, 1.0f));
						m_vertexbuf->texCoord = glm::vec2(s0, t0);
						m_vertexbuf->texID = textureSlot;
						m_vertexbuf->col = m_currentcol;
						++m_vertexbuf;

						m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(x0, y1, 0.0f, 1.0f));
						m_vertexbuf->texCoord = glm::vec2(s0, t1);
						m_vertexbuf->texID = textureSlot;
						m_vertexbuf->col = m_currentcol;
						++m_vertexbuf;

						m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(x1, y1, 0.0f, 1.0f));
						m_vertexbuf->texCoord = glm::vec2(s1, t1);
						m_vertexbuf->texID = textureSlot;
						m_vertexbuf->col = m_currentcol;
						++m_vertexbuf;

						m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(x1, y0, 0.0f, 1.0f));
						m_vertexbuf->texCoord = glm::vec2(s1, t0);
						m_vertexbuf->texID = textureSlot;
						m_vertexbuf->col = m_currentcol;
						++m_vertexbuf;

						m_indexcount += 6;
					}
				}

				return;
			}

			if (m_indexcount + 6 >= RENDERER_INDICES_SIZE) {
				flush();
				begin();
			}

			glm::vec2 size = renderable->getSize();
			glm::vec2 uvstart = renderable->getUVStart();
			glm::vec2 uvend = renderable->getUVEnd();
			GLuint texid = renderable->getTexID();
			glm::mat4 mat = renderable->getTransformationMatrix();

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

			m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(0.0, 0.0, 0.0, 1.0));
			m_vertexbuf->texCoord = glm::vec2(uvstart.x, uvend.y);
			m_vertexbuf->texID = textureSlot;
			m_vertexbuf->col = m_currentcol;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(size.x, 0.0, 0.0, 1.0));
			m_vertexbuf->texCoord = uvend;
			m_vertexbuf->texID = textureSlot;
			m_vertexbuf->col = m_currentcol;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(size.x, size.y, 0.0, 1.0));
			m_vertexbuf->texCoord = glm::vec2(uvend.x, uvstart.y);
			m_vertexbuf->texID = textureSlot;
			m_vertexbuf->col = m_currentcol;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * (mat * glm::vec4(0.0, size.y, 0.0, 1.0));
			m_vertexbuf->texCoord = uvstart;
			m_vertexbuf->texID = textureSlot;
			m_vertexbuf->col = m_currentcol;
			++m_vertexbuf;

			m_indexcount += 6;
		}

		void Renderer::flush() {
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

		void Renderer::flushAll() {
			flush();

			// Draw translucent objects.
			while (m_translucentRenderableList != nullptr) {
				float z = m_translucentRenderableList->self->getPos().z;
				m_font = m_translucentRenderableList->data.font;
				begin();

				m_transformStack.push(m_translucentRenderableList->data.transform, false);
				m_currentcol = m_translucentRenderableList->data.col;

				do {
					submit(m_translucentRenderableList->self, true);
					RenderableData* a = m_translucentRenderableList;
					m_translucentRenderableList = m_translucentRenderableList->next;
					delete a;
				} while (m_translucentRenderableList != nullptr && m_translucentRenderableList->self->getPos().z == z);

				m_transformStack.pop();
				flush();
			}
		}

		void Renderer::queueTranslucentRenderable(Renderable* renderable) {
			RenderableData* rd = m_translucentRenderableList;
			RenderableData* rdprev = nullptr;
			RendererStateData data(m_transformStack.getMatrix(), m_currentcol, m_font);
			
			// This function manipulates the linked list implicitly defined by a chain of RenderableData objects.

			if (rd == nullptr) {
				m_translucentRenderableList = new RenderableData(renderable, data);
				return;
			}

			while (true) {
				if (renderable->getPos().z <= rd->self->getPos().z) {
					// Insert node into linked list.
					if (rdprev == nullptr) {  // Nothing before
						RenderableData* rda = rd;
						m_translucentRenderableList = new RenderableData(renderable, data);
						m_translucentRenderableList->next = rda;
					}
					else {
						rdprev->next = new RenderableData(renderable, data);
						rdprev->next->next = rd;
					}
					return;
				}

				if (rd->next == nullptr) {  // Adding at end of list
					rd->next = new RenderableData(renderable, data);
					return;
				}

				rdprev = rd;
				rd = rd->next;
			}
		}
	}
}
