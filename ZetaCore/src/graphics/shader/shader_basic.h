#pragma once

#include <glm\glm.hpp>
#include "shader.h"

namespace zeta {
	namespace graphics {

		class ShaderBasic : public Shader {

		private:
			GLuint m_locationMatProj;
			GLuint m_locationMatView;
			GLuint m_locationMatModl;

		public:
			ShaderBasic();
			inline void setProjectionMatrix	(glm::mat4& matrix) { glUniformMatrix4fv(m_locationMatProj, 1, GL_FALSE, &matrix[0][0]); }
			inline void setViewMatrix		(glm::mat4& matrix) { glUniformMatrix4fv(m_locationMatView, 1, GL_FALSE, &matrix[0][0]); }
			inline void setModelMatrix		(glm::mat4& matrix) { glUniformMatrix4fv(m_locationMatModl, 1, GL_FALSE, &matrix[0][0]); }
		};
	}
}