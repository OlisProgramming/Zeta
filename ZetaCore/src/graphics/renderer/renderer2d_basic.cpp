#include "renderer2d_basic.h"

#include <glm\gtc\matrix_transform.hpp>
#include "../renderable/static_sprite.h"

namespace zeta {
	namespace graphics {

		Renderer2DBasic::Renderer2DBasic(Shader& shader) : Renderer2D(shader) {
			m_shaderUniformMatProj = m_shader.getUniformLocation("matProj");
			m_shaderUniformMatView = m_shader.getUniformLocation("matView");
			m_shaderUniformMatModl = m_shader.getUniformLocation("matModl");
		}

		void Renderer2DBasic::submit(Renderable2D* renderable) {
			m_renderQueue.push_back(renderable);
		}

		void Renderer2DBasic::flush() {
			m_shader.bind();
			while (!m_renderQueue.empty()) {
				StaticSprite* renderable = static_cast<StaticSprite*>(m_renderQueue.front());
				
				renderable->getVao()->bind();
				renderable->getIbo()->bind();

				glm::mat4 mat = glm::translate(glm::mat4(), renderable->getPos());
				m_shader.setUniformMat4(m_shaderUniformMatModl, mat);
				glDrawElements(GL_TRIANGLES, renderable->getIbo()->getCount(), GL_UNSIGNED_SHORT, NULL);

				renderable->getIbo()->unbind();
				renderable->getVao()->unbind();

				m_renderQueue.pop_front();
			}
			m_shader.unbind();
		}
	}
}