#pragma once

#include "../texture/texture.h"
#include "../buffer/buffer.h"
#include "../buffer/index_buffer.h"
#include "../buffer/vertex_array.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

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
			LABEL,
			GROUP
		};

		class Renderable {
			
		protected:
			glm::vec3 m_pos;
			glm::vec2 m_size;
			Texture* m_tex;
			glm::vec2 m_uvStart;
			glm::vec2 m_uvEnd;
			glm::vec2 m_pivot;
			float m_rot;
			glm::vec2 m_scale;
			bool m_isTranslucent;

		public:
			Renderable(glm::vec3 pos, glm::vec2 size);

			inline const glm::vec3& getPos() const { return m_pos; }
			inline const glm::vec2& getSize() const { return m_size; }
			virtual RenderableType getType() const = 0;
			inline const GLuint getTexID() const { return m_tex==nullptr? 0 : (m_tex->getTexID()); }
			inline const glm::vec2& getUVStart() const { return m_uvStart; }
			inline const glm::vec2& getUVEnd() const { return m_uvEnd; }
			inline const glm::vec2& getPivot() const { return m_pivot; }
			inline const float getRot() const { return m_rot; }
			inline const glm::vec2& getScale() const { return m_scale; }
			inline const bool isTranslucent() const { return m_isTranslucent; }

			inline void setPos(glm::vec3 pos) { m_pos = pos; }
			inline void setPosX(float x) { m_pos.x = x; }
			inline void setPosY(float y) { m_pos.y = y; }
			inline void setPosZ(float z) { m_pos.z = z; }
			inline void setRot(float rot) { m_rot = rot; }
			inline void setScale(glm::vec2 scale) { m_scale = scale; }
			inline void setScaleX(float x) { m_scale.x = x; }
			inline void setScaleY(float y) { m_scale.y = y; }
			inline void setPivot(glm::vec2 pivot) { m_pivot = pivot; }
			inline void setPivotX(float x) { m_pivot.x = x; }
			inline void setPivotY(float y) { m_pivot.y = y; }
			inline void centrePivot() {
				setPivot(getSize() * 0.5f);
			}

			inline glm::mat4 getTransformationMatrix() {

				// First, translate onto pivot point.
				// Scale by m_scale.
				// Rotate on Z axis by m_rot.
				// Translate by m_pos.

				glm::mat4 matPivot = glm::translate(glm::mat4(), glm::vec3(getPivot() * -1.f, 0));
				glm::mat4 matScale = glm::scale(glm::mat4(), glm::vec3(m_scale, 1));
				glm::mat4 matRot = glm::rotate(glm::mat4(), m_rot, glm::vec3(0, 0, 1));
				glm::mat4 matPos = glm::translate(glm::mat4(), m_pos);

				return matPos * matRot * matScale * matPivot;
			}
		};
	}
}