#include "shader_basic.h"

namespace zeta {
	namespace graphics {

		ShaderBasic::ShaderBasic() : Shader("../res/shaders/basic_vert.glsl", "../res/shaders/basic_frag.glsl") {
			bind();
			m_locationMatProj = glGetUniformLocation(m_id, "matProj");
			m_locationMatView = glGetUniformLocation(m_id, "matView");
			m_locationMatModl = glGetUniformLocation(m_id, "matModl");

			GLint texIDs[] = {
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
				10,11,12,13,14,15,16,17,18,19,
				20,21,22,23,24,25,26,27,28,29,
				30,31
			};
			setUniform1iv(getUniformLocation("textures"), 32, texIDs);
		}
	}
}