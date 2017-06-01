#include "renderer2d_basic.h"

#include <glm\gtc\matrix_transform.hpp>
#include "../renderable/static_sprite.h"
#include "../renderable/group2d.h"

namespace zeta {
	namespace graphics {

		Renderer2DBasic::Renderer2DBasic(Shader* shader) : Renderer2D(shader) {
			m_shaderUniformMatProj = m_shader->getUniformLocation("matProj");
			m_shaderUniformMatView = m_shader->getUniformLocation("matView");
			m_shaderUniformMatModl = m_shader->getUniformLocation("matModl");
		}

		void Renderer2DBasic::submit(Renderable2D* renderable) {
			if (renderable->getType() == RenderableType::GROUP) {
				m_transformStack.push((static_cast<Group2D*>(renderable))->getMatrix(), false);
				for (Renderable2D* child : (static_cast<Group2D*>(renderable))->getChildren())
					submit(renderable);
				m_transformStack.pop();
				return;
			}
			
			m_renderQueue.push_back({ renderable, m_transformStack.getMatrix() });
		}

		void Renderer2DBasic::flush() {
			m_shader->bind();
			while (!m_renderQueue.empty()) {
				StaticSprite* renderable = static_cast<StaticSprite*>(m_renderQueue.front().first);
				glm::mat4 transformation = m_renderQueue.front().second;
				
				renderable->getVao()->bind();
				renderable->getIbo()->bind();

				glm::mat4 mat = glm::translate(glm::mat4(), renderable->getPos());
				m_shader->setUniformMat4(m_shaderUniformMatModl, m_transformStack.getMatrix() * mat);
				glDrawElements(GL_TRIANGLES, renderable->getIbo()->getCount(), GL_UNSIGNED_SHORT, NULL);

				renderable->getIbo()->unbind();
				renderable->getVao()->unbind();

				m_renderQueue.pop_front();
			}
			m_shader->unbind();
		}
	}
}