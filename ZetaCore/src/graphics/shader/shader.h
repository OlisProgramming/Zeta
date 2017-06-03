#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

namespace zeta {
	namespace graphics {

		class Shader {

		protected:
			GLuint m_id;
			const char* m_vertpath;
			const char* m_fragpath;

		public:
			Shader(const char* vertexpath, const char* fragpath);
			~Shader();

			inline GLuint getUniformLocation(const char* name)				{ return glGetUniformLocation(m_id, name); }
			inline void setUniform1i  (GLuint location, int value)			{ glUniform1i(location, value); }
			inline void setUniformVec2(GLuint location, glm::vec2& vec)		{ glUniform2fv(location, 1, &vec[0]); }
			inline void setUniformVec3(GLuint location, glm::vec3& vec)		{ glUniform3fv(location, 1, &vec[0]); }
			inline void setUniformVec4(GLuint location, glm::vec4& vec)		{ glUniform4fv(location, 1, &vec[0]); }
			inline void setUniformMat4(GLuint location, glm::mat4& mat)		{ glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]); }

			void bind() const;
			void unbind() const;
		};
	}
}