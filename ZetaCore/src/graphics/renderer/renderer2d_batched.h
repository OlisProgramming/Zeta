#pragma once

#include "renderer2d.h"
#include <freetype-gl.h>

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

		class Renderer2DBatched : public Renderer2D {

		private:
			GLuint m_vao;
			GLuint m_vbo;
			static IndexBuffer* m_ibo;
			GLsizei m_indexcount;
			VertexData* m_vertexbuf;
			unsigned int m_currentcol;  // The current colour of the renderer. This 'dyes' the renderables this colour (white is normal colour)
			std::vector<GLuint> m_textureSlots;
			
			ftgl::texture_atlas_t* m_fontAtlas;
			ftgl::texture_font_t* m_font;
			
		public:
			Renderer2DBatched(Shader* shader);
			~Renderer2DBatched();
			static void init();

			void begin() override;
			void submit(Renderable2D* renderable) override;
			void flush() override;

			inline void setColour(glm::vec3 col) {
				int r = (int)(col.x * 255);
				int g = (int)(col.y * 255);
				int b = (int)(col.z * 255);
				int a = 255;
				m_currentcol = a << 24 | b << 16 | g << 8 | r;
			}
		};
	}
}