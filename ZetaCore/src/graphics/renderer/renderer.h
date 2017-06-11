#pragma once

#include <glm\glm.hpp>
#include <freetype-gl.h>
#include "transformation_stack.h"
#include "../renderable/renderable.h"
#include "../font/font.h"
#include "../font/font_manager.h"
#include "../shader/shader.h"

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
			Renderable* self;
			RenderableData* next;
			RendererStateData data;
			RenderableData(Renderable* self, RendererStateData data) : self(self), next(nullptr), data(data) {}
		};

		class Renderer {

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
			Shader* m_shader;
			TransformationStack m_transformStack;
			
		public:
			Renderer(Shader* shader);
			~Renderer();
			static void init();

			void begin();
			void submit(Renderable* renderable);
		private:
			void submit(Renderable* renderable, bool renderTranslucentImmediately);
		public:
			void flush();
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

			// If specified font does not exist, the renderer will use the default font (size 15 Consolas).
			inline void setFont(const std::string& fname, unsigned int size) {
				setFont(FontManager::inst->get(fname, size));
			}

			inline Shader* getShader() { return m_shader; }
			inline Font* getFont() { return m_font; }

			inline void transformationPush(glm::mat4 mat, bool doOverride = false) { m_transformStack.push(mat, doOverride); }
			inline void transformationPop() { m_transformStack.pop(); }

		private:
			void queueTranslucentRenderable(Renderable* renderable);
		};
	}
}