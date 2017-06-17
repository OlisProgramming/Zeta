#pragma once

#include <glm\glm.hpp>
#include "../shader/shader.h"

namespace zeta {
	namespace graphics {

		// An orthographic camera implementation.
		class Camera {

		private:
			Shader* m_shader;
			GLuint m_shaderLocationView;
			GLuint m_shaderLocationProj;
			glm::vec2 m_pos;
			glm::mat4 m_proj, m_view;
			glm::vec2 m_windowDimensions;

		public:
			Camera(Shader* shader, glm::vec2 windowDimensions);
			inline const glm::vec2& getPos() const { return m_pos; }
			inline const float getX() const { return m_pos.x; }
			inline const float getY() const { return m_pos.y; }
			inline void setPos(glm::vec2& pos) { m_pos = pos; }
			inline void setX(float x) { m_pos.x = x; }
			inline void setY(float y) { m_pos.y = y; }
			// Recalculates the view and projection matrices and sends them to OpenGL.
			void recomputeMatrices();
		};
	}
}