#include "shader.h"

#include <vector>
#include "../../util/fileutils.h"

namespace zeta {
	namespace graphics {

		Shader::Shader(const char* vertexpath, const char* fragpath) :
			m_vertpath(vertexpath), m_fragpath(fragpath) {
			
			GLuint program = glCreateProgram();

			GLuint vertshader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragshader = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertsource = util::readFileText(vertexpath);
			std::string fragsource = util::readFileText(fragpath);

			const char* vertsourcec = vertsource.c_str();
			const char* fragsourcec = fragsource.c_str();

			glShaderSource(vertshader, 1, &vertsourcec, NULL);
			glCompileShader(vertshader);

			GLint result;
			glGetShaderiv(vertshader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(vertshader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> msg(length);
				glGetShaderInfoLog(vertshader, length, &length, &msg[0]);
				fprintf(stderr, "OpenGL error when compiling vertex shader %s:\n%s\n", vertexpath, &msg[0]);
				glDeleteShader(vertshader);
				return;
			}

			glShaderSource(fragshader, 1, &fragsourcec, NULL);
			glCompileShader(fragshader);

			glGetShaderiv(fragshader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(fragshader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> msg(length);
				glGetShaderInfoLog(fragshader, length, &length, &msg[0]);
				fprintf(stderr, "OpenGL error when compiling fragment shader %s:\n%s\n", fragpath, &msg[0]);
				glDeleteShader(fragshader);
				return;
			}

			glAttachShader(program, vertshader);
			glAttachShader(program, fragshader);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertshader);
			glDeleteShader(fragshader);

			m_id = program;
		}

		Shader::~Shader() {
		}

		void Shader::bind() const {
			glUseProgram(m_id);
		}

		void Shader::unbind() const {
		}
	}
}
