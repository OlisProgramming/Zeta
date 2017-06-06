#pragma once

#include "renderer2d.h"
#include <freetype-gl.h>
#include "../font/font.h"

namespace zeta {
	namespace graphics {

#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	(sizeof(VertexData))
#define RENDERER_SPRITE_SIZE	(RENDERER_VERTEX_SIZE*4)
#define RENDERER_BUFFER_SIZE	(RENDERER_SPRITE_SIZE*RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE	(RENDERER_MAX_SPRITES*6)

#define SHADER_VERTEX_INDEX		0
#define SHADER_TEXCOORD_INDEX	1
#define SHADER_TEXID_INDEX		2
#define SHADER_COL_INDEX		3

		struct RendererStateData {
			glm::mat4 transform;
			unsigned int col;
			Font* font;
			RendererStateData(glm::mat4& transform, unsigned int col, Font* font) : transform(transform), col(col), font(font) {}
		};

		struct RenderableData {
			Renderable2D* self;
			RenderableData* next;
			RendererStateData data;
			RenderableData(Renderable2D* self, RendererStateData data) : self(self), next(nullptr), data(data) {}
		};

		class Renderer2DBatched : public Renderer2D {

		private:
			GLuint m_vao;
			GLuint m_vbo;
			static IndexBuffer* m_ibo;
			GLsizei m_indexcount;
			VertexData* m_vertexbuf;
			unsigned int m_currentcol;  // The current colour of the renderer. This 'dyes' the renderables this colour (white is normal colour)
			std::vector<GLuint> m_textureSlots;
			RenderableData* m_translucentRenderableList;
			Font* m_font, *m_defaultfont;

			//ftgl::texture_atlas_t* m_fontAtlas;
			//ftgl::texture_font_t* m_font;
			
		public:
			Renderer2DBatched(Shader* shader);
			~Renderer2DBatched();
			static void init();

			void begin() override;
			void submit(Renderable2D* renderable) override;
		private:
			void submit(Renderable2D* renderable, bool renderTranslucentImmediately);
		public:
			void flush() override;
			void flushAll();

			inline void setColour(glm::vec4 col) {
				int r = (int)(col.x * 255);
				int g = (int)(col.y * 255);
				int b = (int)(col.z * 255);
				int a = (int)(col.w * 255);
				m_currentcol = a << 24 | b << 16 | g << 8 | r;
			}

			// Pass nullptr to set to default font.
			inline void setFont(Font* font) {
				if (m_font == font) {
					return;
				}
				if (font == nullptr) {
					font = m_defaultfont;
				}
				flush();
				m_font = font;
				begin();
			}

		private:
			void queueTranslucentRenderable(Renderable2D* renderable);
		};
	}
}