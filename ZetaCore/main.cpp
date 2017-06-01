#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "src\graphics\window.h"
#include "src\graphics\renderable\static_sprite.h"
#include "src\graphics\renderer\renderer2d_batched.h"
#include "src\graphics\layer\map_layer.h"
#include "src\graphics\renderable\sprite.h"
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
	layer.submit(new Sprite(glm::vec3(0,0,0), glm::vec2(90,90)));

	FPSClock clock;
	while (!wnd.shouldClose()) {
		wnd.drawStart();
		layer.render();
		wnd.drawEnd();

		clock.tick();
		printf("%f FPS\n", clock.getFPS());
	}

	return 0;
}