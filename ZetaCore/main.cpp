#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "src\graphics\window.h"
#include "src\graphics\shader_basic.h"
#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\index_buffer.h"
#include "src\graphics\buffers\vertex_array.h"
#include "src\input\input_interface.h"
#include "src\util\fileutils.h"

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;

	Window wnd("Zeta Engine", 800, 600);
	ShaderBasic shader;
	shader.bind();

	glm::mat4 proj = glm::ortho(0.0, 800.0, 600.0, 0.0);
	shader.setProjectionMatrix(proj);
	GLuint lightPos = shader.getUniformLocation("lightPos");

	GLfloat data[] = {
		100.0f, 500.0f, 0.0f, 1.0f,
		100.0f, 100.0f, 0.0f, 1.0f,
		700.0f, 100.0f, 0.0f, 1.0f,
		700.0f, 500.0f, 0.0f, 1.0f
	};
	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray vao;
	Buffer* vbo = new Buffer(data, 4 * 4, 4);
	IndexBuffer ibo(indices, 6);
	vao.addBuffer(vbo, 0);

	while (!wnd.shouldClose()) {
		wnd.drawStart();

		shader.setUniformVec2(lightPos, glm::vec2(zeta::input::InputInterface::inst->mouseX(), zeta::input::InputInterface::inst->mouseY()));

		vao.bind();
		ibo.bind();
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		vao.unbind();

		wnd.drawEnd();
	}

	return 0;
}