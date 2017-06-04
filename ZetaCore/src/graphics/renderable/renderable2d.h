#pragma once

#include "texture.h"
#include "../buffer/buffer.h"
#include "../buffer/index_buffer.h"
#include "../buffer/vertex_array.h"
#include <glm\glm.hpp>

namespace zeta {
	namespace graphics {

		struct VertexData {
			glm::vec3 pos;  // X Y Z
			glm::vec2 texCoord;  // U V
			GLfloat texID;
		};

		enum class RenderableType {
			SPRITE,
			STATIC_SPRITE,
			LABEL,
			GROUP
		};

		class Renderable2D {
			
		protected:
			glm::vec3 m_pos;
			glm::vec2 m_size;
			Texture* m_tex;

		public:
			Renderable2D(glm::vec3 pos, glm::vec2 size);

			inline const glm::vec3& getPos() const { return m_pos; }
			inline const glm::vec2& getSize() const { return m_size; }
			virtual RenderableType getType() const = 0;
			inline const GLuint getTexID() const { return m_tex==nullptr? 0 : (m_tex->getTexID()); }
		};
	}
}