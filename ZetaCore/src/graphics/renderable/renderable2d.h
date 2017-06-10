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
			unsigned int col;
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
			glm::vec2 m_uvStart;
			glm::vec2 m_uvEnd;
			bool m_isTranslucent;

		public:
			Renderable2D(glm::vec3 pos, glm::vec2 size);

			inline const glm::vec3& getPos() const { return m_pos; }
			inline const glm::vec2& getSize() const { return m_size; }
			virtual RenderableType getType() const = 0;
			inline const GLuint getTexID() const { return m_tex==nullptr? 0 : (m_tex->getTexID()); }
			inline const glm::vec2& getUVStart() const { return m_uvStart; }
			inline const glm::vec2& getUVEnd() const { return m_uvEnd; }
			inline const bool isTranslucent() const { return m_isTranslucent; }
		};
	}
}