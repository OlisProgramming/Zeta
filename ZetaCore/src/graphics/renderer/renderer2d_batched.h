#pragma once

#include "renderer2d.h"

namespace zeta {
	namespace graphics {

#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE	(sizeof(VertexData))
#define RENDERER_SPRITE_SIZE	(RENDERER_VERTEX_SIZE*4)
#define RENDERER_BUFFER_SIZE	(RENDERER_SPRITE_SIZE*RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE	(RENDERER_MAX_SPRITES*6)

#define SHADER_VERTEX_INDEX		0
#define SHADER_TEXCOORD_INDEX	1

		class Renderer2DBatched : public Renderer2D {

		private:
			GLuint m_vao;
			GLuint m_vbo;
			static IndexBuffer* m_ibo;
			GLsizei m_indexcount;
			VertexData* m_vertexbuf;
			
		public:
			Renderer2DBatched(Shader* shader);
			~Renderer2DBatched();
			static void init();

			void begin() override;
			void submit(Renderable2D* renderable) override;
			void flush() override;
		};
	}
}