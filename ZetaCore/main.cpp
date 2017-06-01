#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "src\graphics\window.h"
#include "src\graphics\shader_basic.h"
#include "src\graphics\buffer\buffer.h"
#include "src\graphics\buffer\index_buffer.h"
#include "src\graphics\buffer\vertex_array.h"
#include "src\graphics\renderer\renderer2d_basic.h"
#include "src\graphics\renderer\renderer2d_batched.h"
#include "src\graphics\renderable\static_sprite.h"
#include "src\graphics\renderable\sprite.h"
#include "src\input\input_interface.h"
#include "src\util\fileutils.h"
#include "src\util\fps_clock.h"

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;
	using namespace util;

	Window wnd("Zeta Engine", 800, 600);

	StaticSprite::init();  // Sets up IBOs
	Renderer2DBatched::init();
	ShaderBasic shader;
	shader.bind();

	glm::mat4 proj = glm::ortho(0.0, 800.0, 600.0, 0.0, 0.1, 1000.0);
	shader.setProjectionMatrix(proj);
	glm::mat4 view = glm::translate(glm::mat4(), {0.0, 0.0, -500.0});
	shader.setViewMatrix(view);
	GLuint lightPos = shader.getUniformLocation("lightPos");

	Renderer2DBatched renderer(shader);
	std::vector<Sprite*> sprites;
	for (int i = 0; i < 800; i += 5) {
		for (int j = 0; j < 600; j += 5) {
			sprites.push_back(new Sprite({i, j, 0}, {3, 3}));
		}
	}

	FPSClock clock;
	while (!wnd.shouldClose()) {
		wnd.drawStart();

		shader.setUniformVec2(lightPos, glm::vec2(zeta::input::InputInterface::inst->mouseX(), zeta::input::InputInterface::inst->mouseY()));

		renderer.begin();
		for (unsigned int i = 0; i < sprites.size(); ++i)
			renderer.submit(sprites[i]);
		renderer.flush();

		wnd.drawEnd();

		clock.tick();
		printf("%f FPS\n", clock.getFPS());
	}

	return 0;
}