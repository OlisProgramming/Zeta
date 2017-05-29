#pragma once

#include "../buffers/buffer.h"
#include "../buffers/index_buffer.h"
#include "../buffers/vertex_array.h"
#include <glm\glm.hpp>

namespace zeta {
	namespace graphics {

		class Renderable2D {
			
		protected:
			glm::vec3 m_pos;
			glm::vec2 m_size;

			VertexArray* m_vao;
			static IndexBuffer* m_ibo;

		public:
			static void init();
			Renderable2D(glm::vec3 pos, glm::vec2 size);
			virtual ~Renderable2D();

			inline const VertexArray* getVao() const { return m_vao; }
			inline const IndexBuffer* getIbo() const { return m_ibo; }

			inline const glm::vec3& getPos() const { return m_pos; }
			inline const glm::vec2& getSize() const { return m_size; }
		};
	}
}