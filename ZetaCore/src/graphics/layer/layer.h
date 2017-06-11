#pragma once

#include "../renderer/renderer.h"

namespace zeta {
	namespace graphics {

		class Layer {
		protected:
			Renderer* m_renderer;
			std::vector<Renderable*> m_renderables;
			glm::mat4 m_projMat;

		protected:
			Layer(Renderer* renderer, glm::mat4 projMat);
		public:
			virtual ~Layer();
			virtual void submit(Renderable* renderable);
			virtual void render();
			inline Renderer* getRenderer() const { return m_renderer; }
		};
	}
}