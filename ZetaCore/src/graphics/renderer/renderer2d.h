#pragma once

#include "../renderable/renderable2d.h"
#include "../shader/shader.h"

namespace zeta {
	namespace graphics {

		class Renderer2D {

		protected:
			Shader* m_shader;

		public:
			Renderer2D(Shader* shader) : m_shader(shader) {}
			virtual inline ~Renderer2D() { delete m_shader; }
			virtual void begin() {};
			virtual void submit(Renderable2D* renderable) = 0;
			virtual void flush() = 0;
			inline Shader* getShader() { return m_shader; }
		};
	}
}