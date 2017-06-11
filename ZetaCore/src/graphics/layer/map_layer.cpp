#include "map_layer.h"

#include <glm\gtc\matrix_transform.hpp>
#include "../renderer/renderer.h"
#include "../shader/shader_basic.h"

namespace zeta {
	namespace graphics {

		MapLayer::MapLayer(int w, int h) :
			Layer(new Renderer(new ShaderBasic()), glm::ortho(0.0, (double)w, (double)h, 0.0, 0.1, 1000.0)) {
			m_renderer->getShader()->setUniformMat4(m_renderer->getShader()->getUniformLocation("matView"), glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -500.f)));
		}
	}
}