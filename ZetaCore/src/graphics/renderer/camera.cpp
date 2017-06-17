#include "camera.h"

#include <glm\gtc\matrix_transform.hpp>

namespace zeta {
	namespace graphics {

		Camera::Camera(Shader* shader, glm::vec2 windowDimensions) :
			m_shader(shader), m_windowDimensions(windowDimensions) {
			m_shader->bind();
			m_shaderLocationProj = shader->getUniformLocation("matProj");
			m_shaderLocationView = shader->getUniformLocation("matView");
			recomputeMatrices();
		}

		void Camera::recomputeMatrices() {

			m_proj = glm::ortho(0.0f, m_windowDimensions.x, m_windowDimensions.y, 0.0f, 0.1f, 1000000.0f);
			m_view = glm::translate(glm::mat4(), glm::vec3(m_pos*-1.f, -500000.0f));

			// Send to OpenGL
			m_shader->bind();
			m_shader->setUniformMat4(m_shaderLocationProj, m_proj);
			m_shader->setUniformMat4(m_shaderLocationView, m_view);
		}
	}
}