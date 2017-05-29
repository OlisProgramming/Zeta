#include "static_sprite.h"

namespace zeta {
	namespace graphics {

		IndexBuffer* StaticSprite::m_ibo;

		void StaticSprite::init() {
			GLushort indices[] = {
				0,1,2,2,3,0
			};
			m_ibo = new IndexBuffer(indices, 6);
		}

		StaticSprite::StaticSprite(glm::vec3 pos, glm::vec2 size) :
			Renderable2D(pos, size) {

			m_vao = new VertexArray;
			GLfloat vertices[] = {
				0.0f,   0.0f,   0.0f,
				0.0f,   size.y, 0.0f,
				size.x, size.y, 0.0f,
				size.x, 0.0f,   0.0f
			};
			m_vao->addBuffer(new Buffer(vertices, 12, 3), 0);
		}

		StaticSprite::~StaticSprite() {
			delete m_vao;
		}
	}
}
