#include "map_layer.h"

#include <glm\gtc\matrix_transform.hpp>
#include "../renderer/renderer2d_batched.h"
#include "../shader/shader_basic.h"

namespace zeta {
	namespace graphics {

		MapLayer::MapLayer(int w, int h) :
			Layer(new Renderer2DBatched(new ShaderBasic()), glm::ortho(0.0, (double)w, (double)h, 0.0, 0.1, 1000.0)) {
			m_renderer->getShader()->setUniformMat4(m_renderer->getShader()->getUniformLocation("matView"), glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -500.f)));
			
			m_renderer->transformationPush(glm::translate(glm::mat4(), glm::vec3(-400.0f, -300.0f, 0.0f)));
			m_renderer->transformationPush(glm::rotate(glm::mat4(), glm::quarter_pi<float>(), glm::vec3(0, 0, 1)));
			m_renderer->transformationPush(glm::translate(glm::mat4(), glm::vec3(400.0f, 300.0f, 0.0f)));
		}
	}
}