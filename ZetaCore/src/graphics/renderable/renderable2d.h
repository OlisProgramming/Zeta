#pragma once

#include "../buffers/buffer.h"
#include "../buffers/index_buffer.h"
#include "../buffers/vertex_array.h"
#include <glm\glm.hpp>

namespace zeta {
	namespace graphics {

		struct VertexData {
			glm::vec3 pos;
		};

		class Renderable2D {
			
		protected:
			glm::vec3 m_pos;
			glm::vec2 m_size;

		public:
			Renderable2D(glm::vec3 pos, glm::vec2 size);

			inline const glm::vec3& getPos() const { return m_pos; }
			inline const glm::vec2& getSize() const { return m_size; }
		};
	}
}