#include "shader_basic.h"

namespace zeta {
	namespace graphics {

		ShaderBasic::ShaderBasic() : Shader("../res/shaders/basic_vert.glsl", "../res/shaders/basic_frag.glsl") {
			m_locationMatProj = glGetUniformLocation(m_id, "matProj");
			m_locationMatView = glGetUniformLocation(m_id, "matView");
			m_locationMatModl = glGetUniformLocation(m_id, "matModl");
		}
	}
}