#include "renderer2d_batched.h"
#include "../renderable/group2d.h"
#include "../renderable/label.h"

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

			// Initialise ftgl

			m_fontAtlas = ftgl::texture_atlas_new(512, 512, 1);
			m_font = ftgl::texture_font_new_from_file(m_fontAtlas, 15, "../res/fonts/font.ttf");

			for (char a = 32; a < 126; ++a)  // Pre-initialise font data.
				ftgl::texture_font_get_glyph(m_font, a);

			setColour({1, 1, 1, 1});

			m_translucentRenderableList = nullptr;
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
			m_vertexbuf = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

			m_textureSlots.clear();
			m_textureSlots.push_back(m_fontAtlas->id);  // Force font texture to occupy sampler location 0.
		}

		void Renderer2DBatched::submit(Renderable2D* renderable) {
			submit(renderable, false);
		}

		void Renderer2DBatched::submit(Renderable2D* renderable, bool renderTranslucentImmediately) {

			if (renderable->isTranslucent() && !renderTranslucentImmediately) {
				queueTranslucentRenderable(renderable);
				return;
			}

			if (renderable->getType() == RenderableType::GROUP) {
				m_transformStack.push((static_cast<Group2D*>(renderable))->getMatrix(), false);
				for (Renderable2D* child : (static_cast<Group2D*>(renderable))->getChildren())
					submit(child);
				m_transformStack.pop();
				return;
			}
			else if (renderable->getType() == RenderableType::LABEL) {
				Label* label = static_cast<Label*>(renderable);
				
				// DRAW STRING
				float textureSlot = 0.0f;
				bool found = false;
				for (unsigned int i = 0; i < m_textureSlots.size(); ++i) {
					if (m_textureSlots[i] == m_fontAtlas->id) {
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
					m_textureSlots.push_back(m_fontAtlas->id);
					textureSlot = (float)(m_textureSlots.size());
				}

				glm::vec3 pos = renderable->getPos();
				glm::vec2 size(512, 512);
				std::string s = label->getString();

				if (m_indexcount + 6 * s.length() >= RENDERER_INDICES_SIZE) {
					flush();
					begin();
				}

				float offset = 0.0f;

				for (unsigned int i = 0; i < s.length(); ++i) {

					char c = s[i];
					ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(m_font, c);
					if (glyph != NULL) {

						float x0 = pos.x + glyph->offset_x + offset;
						float y0 = pos.y - glyph->offset_y;
						float x1 = x0 + glyph->width;
						float y1 = y0 + glyph->height;

						float s0 = glyph->s0;
						float t0 = glyph->t0;
						float s1 = glyph->s1;
						float t1 = glyph->t1;

						offset += glyph->advance_x;

						m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(x0, y0, pos.z, 1.0f);
						m_vertexbuf->texCoord = glm::vec2(s0, t0);
						m_vertexbuf->texID = textureSlot;
						m_vertexbuf->col = m_currentcol;
						++m_vertexbuf;

						m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(x0, y1, pos.z, 1.0f);
						m_vertexbuf->texCoord = glm::vec2(s0, t1);
						m_vertexbuf->texID = textureSlot;
						m_vertexbuf->col = m_currentcol;
						++m_vertexbuf;

						m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(x1, y1, pos.z, 1.0f);
						m_vertexbuf->texCoord = glm::vec2(s1, t1);
						m_vertexbuf->texID = textureSlot;
						m_vertexbuf->col = m_currentcol;
						++m_vertexbuf;

						m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(x1, y0, pos.z, 1.0f);
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
			m_vertexbuf->col = m_currentcol;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(pos.x+size.x, pos.y, pos.z, 1.0);
			m_vertexbuf->texCoord = glm::vec2(1, 0);
			m_vertexbuf->texID = textureSlot;
			m_vertexbuf->col = m_currentcol;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(pos.x+size.x, pos.y+size.y, pos.z, 1.0);
			m_vertexbuf->texCoord = glm::vec2(1, 1);
			m_vertexbuf->texID = textureSlot;
			m_vertexbuf->col = m_currentcol;
			++m_vertexbuf;
			
			m_vertexbuf->pos = m_transformStack.getMatrix() * glm::vec4(pos.x, pos.y+size.y, pos.z, 1.0);
			m_vertexbuf->texCoord = glm::vec2(0, 1);
			m_vertexbuf->texID = textureSlot;
			m_vertexbuf->col = m_currentcol;
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

		void Renderer2DBatched::flushAll() {
			flush();

			// Draw translucent objects.
			while (m_translucentRenderableList != nullptr) {
				begin();
				m_transformStack.push(m_translucentRenderableList->data.transform, false);
				m_currentcol = m_translucentRenderableList->data.col;
				submit(m_translucentRenderableList->self, true);
				m_transformStack.pop();
				flush();
				RenderableData* a = m_translucentRenderableList;
				m_translucentRenderableList = m_translucentRenderableList->next;
				delete a;
			}
		}

		void Renderer2DBatched::queueTranslucentRenderable(Renderable2D* renderable) {
			RenderableData* rd = m_translucentRenderableList;
			RenderableData* rdprev = nullptr;
			RendererStateData data(m_transformStack.getMatrix(), m_currentcol);
			
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
