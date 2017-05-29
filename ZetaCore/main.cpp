#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "src\graphics\window.h"
#include "src\graphics\shader_basic.h"
#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\index_buffer.h"
#include "src\graphics\buffers\vertex_array.h"
#include "src\graphics\renderer\renderer2d_basic.h"
#include "src\input\input_interface.h"
#include "src\util\fileutils.h"

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;

	Window wnd("Zeta Engine", 800, 600);
	Renderable2D::init();  // Sets up IBOs
	ShaderBasic shader;
	shader.bind();

	glm::mat4 proj = glm::ortho(0.0, 800.0, 600.0, 0.0, 0.1, 1000.0);
	shader.setProjectionMatrix(proj);
	glm::mat4 view = glm::translate(glm::mat4(), {0.0, 0.0, -500.0});
	shader.setViewMatrix(view);
	GLuint lightPos = shader.getUniformLocation("lightPos");

	Renderer2DBasic renderer(shader);
	std::vector<Renderable2D*> sprites;
	for (int i = 0; i < 50; ++i)
		sprites.push_back(new Renderable2D({i*15, 20, i-25}, {10, 100}));

	while (!wnd.shouldClose()) {
		wnd.drawStart();

		shader.setUniformVec2(lightPos, glm::vec2(zeta::input::InputInterface::inst->mouseX(), zeta::input::InputInterface::inst->mouseY()));

		for (int i = 0; i < 50; ++i)
			renderer.submit(sprites[i]);
		renderer.flush();

		wnd.drawEnd();
	}

	return 0;
}