#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "src\graphics\window.h"
#include "src\graphics\renderable\static_sprite.h"
#include "src\graphics\renderer\renderer2d_batched.h"
#include "src\graphics\layer\map_layer.h"
#include "src\graphics\renderable\group2d.h"
#include "src\graphics\renderable\sprite.h"
#include "src\graphics\renderable\texture.h"
#include "src\util\fps_clock.h"

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;
	using namespace util;

	Window wnd("Zeta Engine", 800, 600);

	// Set up static IBOs
	StaticSprite::init();
	Renderer2DBatched::init();

	MapLayer layer(800, 600);
	layer.submit(new Sprite(glm::vec3(10, 10, 0), glm::vec2(100, 100)));

	Group2D* group = new Group2D(glm::translate(glm::mat4(), glm::vec3(400, 300, 0)));
	group->submit(new Sprite(glm::vec3(-5, -20, 0), glm::vec2(10, 40)));
	group->submit(new Sprite(glm::vec3(-20, -5, 0), glm::vec2(40, 10)));
	layer.submit(group);

	layer.submit(new Sprite(glm::vec3(690, 490, 0), glm::vec2(100, 100)));

	glActiveTexture(GL_TEXTURE0);
	Texture tex("../res/textures/test.png");
	tex.bind();

	layer.getRenderer()->getShader()->bind();
	layer.getRenderer()->getShader()->setUniform1i(layer.getRenderer()->getShader()->getUniformLocation("tex"), 0);

	FPSClock clock;
	while (!wnd.shouldClose()) {
		wnd.drawStart();
		layer.render();
		wnd.drawEnd();

		clock.tick();
		//printf("%f FPS\n", clock.getFPS());
	}

	return 0;
}
