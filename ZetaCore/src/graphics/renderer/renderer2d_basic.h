#pragma once

#include "renderer2d.h"
#include <deque>

namespace zeta {
	namespace graphics {

		class Renderer2DBasic : public Renderer2D {

		private:
			std::deque<Renderable2D*> m_renderQueue;
			GLuint m_shaderUniformMatProj;
			GLuint m_shaderUniformMatView;
			GLuint m_shaderUniformMatModl;

		public:
			Renderer2DBasic(Shader* shader);
			void submit(Renderable2D* renderable) override;
			void flush() override;
		};
	}
}