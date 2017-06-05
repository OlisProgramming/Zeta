#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "src\graphics\window.h"
#include "src\graphics\renderable\static_sprite.h"
#include "src\graphics\renderer\renderer2d_batched.h"
#include "src\graphics\renderable\group2d.h"
#include "src\graphics\renderable\sprite.h"
#include "src\graphics\renderable\texture.h"
#include "src\graphics\renderable\label.h"
#include "src\graphics\shader\shader_basic.h"
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

	ShaderBasic* shader = new ShaderBasic;
	Renderer2DBatched renderer(shader);
	shader->bind();
	glm::mat4 ortho = glm::ortho(0.0, 800.0, 600.0, 0.0, 0.1, 1000000.0);
	glm::mat4 view = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -500000.0f));
	shader->setUniformMat4(shader->getUniformLocation("matProj"), ortho);
	shader->setUniformMat4(shader->getUniformLocation("matView"), view);

	Group2D objects({0, 0, 0});
	objects.submit(new Sprite(glm::vec3(10, 10, 0), glm::vec2(100, 100), &texa, true));

	Group2D* group = new Group2D(glm::translate(glm::mat4(), glm::vec3(400, 300, 0)));
	group->submit(new Sprite(glm::vec3(-5, -20, 10), glm::vec2(10, 40), &tex, true));
	group->submit(new Sprite(glm::vec3(-20, -5, 20), glm::vec2(40, 10), &tex, true));
	objects.submit(group);

	objects.submit(new Sprite(glm::vec3(690, 490, 5), glm::vec2(100, 100), &texa, true));

	Group2D fpsgroup({ 5, 20, 0 });
	Label* fpscounter = new Label("100 FPS", { 0, 0, 500 }, true);
	fpsgroup.submit(fpscounter);

	GLint texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31
	};

	shader->bind();
	shader->setUniform1iv(shader->getUniformLocation("textures"), 32, texIDs);

	FPSClock clock;
	while (!wnd.shouldClose()) {
		wnd.drawStart();

		renderer.begin();
		
		renderer.setColour({ 1, 1, 1, 1 });
		renderer.submit(&objects);

		renderer.setColour({ 1, 1, 1, 0.5 });
		renderer.submit(&fpsgroup);

		renderer.flushAll();

		wnd.drawEnd();

		clock.tick();
		fpscounter->setString(std::to_string((int)clock.getFPS()) + " FPS");
		//printf("%f FPS\n", clock.getFPS());
	}

	return 0;
}
