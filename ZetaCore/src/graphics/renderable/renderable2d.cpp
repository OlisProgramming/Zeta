#include "renderable2d.h"

namespace zeta {
	namespace graphics {

		IndexBuffer* Renderable2D::m_ibo;

		void Renderable2D::init() {
			GLushort indices[] = {
				0,1,2,2,3,0
			};
			m_ibo = new IndexBuffer(indices, 6);
		}

		Renderable2D::Renderable2D(glm::vec3 pos, glm::vec2 size) :
			m_pos(pos), m_size(size) {
			m_vao = new VertexArray;
			GLfloat vertices[] = {
				0.0f,   0.0f,   0.0f,
				0.0f,   size.y, 0.0f,
				size.x, size.y, 0.0f,
				size.x, 0.0f,   0.0f
			};
			m_vao->addBuffer(new Buffer(vertices, 12, 3), 0);
		}

		Renderable2D::~Renderable2D() {
			delete m_vao;
		}
	}
}