#pragma once

#include "renderable2d.h"

namespace zeta {
	namespace graphics {

		class StaticSprite : public Renderable2D {

		private:
			VertexArray* m_vao;
			static IndexBuffer* m_ibo;

		public:
			static void init();
			StaticSprite(glm::vec3 pos, glm::vec2 size);
			virtual ~StaticSprite();
			inline RenderableType getType() const override { return RenderableType::STATIC_SPRITE; }

			inline const VertexArray* getVao() const { return m_vao; }
			inline const IndexBuffer* getIbo() const { return m_ibo; }
		};
	}
}