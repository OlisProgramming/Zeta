#include "layer.h"

namespace zeta {
	namespace graphics {

		Layer::Layer(Renderer2D* renderer, glm::mat4 projMat) :
			m_renderer(renderer), m_projMat(projMat) {

			m_renderer->getShader()->bind();
			m_renderer->getShader()->setUniformMat4(m_renderer->getShader()->getUniformLocation("matProj"), m_projMat);
			m_renderer->getShader()->unbind();
		}

		Layer::~Layer() {
			delete m_renderer;
			for (Renderable2D* renderable : m_renderables)
				delete renderable;
		}

		void Layer::submit(Renderable2D* renderable) {
			m_renderables.push_back(renderable);
		}

		void Layer::render() {
			m_renderer->getShader()->bind();

			m_renderer->begin();
			for (Renderable2D* renderable : m_renderables) {
				m_renderer->submit(renderable);
			}
			m_renderer->flush();

			m_renderer->getShader()->unbind();
		}
	}
}