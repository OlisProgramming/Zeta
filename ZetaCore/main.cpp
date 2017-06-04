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

#include <ft2build.h>
#include <freetype\freetype.h>
#include <freetype-gl.h>

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;
	using namespace util;

	Window wnd("Zeta Engine", 800, 600);

	// Set up static IBOs
	StaticSprite::init();
	Renderer2DBatched::init();

	Texture tex("../res/textures/test.png");
	Texture texa("../res/textures/testa.png");

	MapLayer layer(800, 600);
	layer.submit(new Sprite(glm::vec3(10, 10, 0), glm::vec2(100, 100), &texa));

	Group2D* group = new Group2D(glm::translate(glm::mat4(), glm::vec3(400, 300, 0)));
	group->submit(new Sprite(glm::vec3(-5, -20, 0), glm::vec2(10, 40), &tex));
	group->submit(new Sprite(glm::vec3(-20, -5, 0), glm::vec2(40, 10), &tex));
	layer.submit(group);

	layer.submit(new Sprite(glm::vec3(690, 490, 0), glm::vec2(100, 100), &texa));

	GLint texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31
	};

	layer.getRenderer()->getShader()->bind();
	layer.getRenderer()->getShader()->setUniform1iv(layer.getRenderer()->getShader()->getUniformLocation("textures"), 32, texIDs);

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
