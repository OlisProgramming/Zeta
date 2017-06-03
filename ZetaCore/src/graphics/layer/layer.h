#pragma once

#include "../renderer/renderer2d.h"

namespace zeta {
	namespace graphics {

		class Layer {
		protected:
			Renderer2D* m_renderer;
			std::vector<Renderable2D*> m_renderables;
			glm::mat4 m_projMat;

		protected:
			Layer(Renderer2D* renderer, glm::mat4 projMat);
		public:
			virtual ~Layer();
			virtual void submit(Renderable2D* renderable);
			virtual void render();
			inline Renderer2D* getRenderer() const { return m_renderer; }
		};
	}
}