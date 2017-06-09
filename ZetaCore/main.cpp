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
#include "src\util\mathutil.h"
#include "src\sound\sound_manager.h"

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;
	using namespace sound;
	using namespace util;

	Window wnd("Zeta Engine", 800, 600);

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
	objects.submit(new Sprite(glm::vec3(10, 10, 0), glm::vec2(100, 100), &texa));

	Group2D* group = new Group2D(glm::translate(glm::mat4(), glm::vec3(400, 300, 0)));
	group->submit(new Sprite(glm::vec3(-5, -20, 10), glm::vec2(10, 40), &tex));
	group->submit(new Sprite(glm::vec3(-20, -5, 20), glm::vec2(40, 10), &tex));
	objects.submit(group);

	objects.submit(new Sprite(glm::vec3(690, 490, 5), glm::vec2(100, 100), &texa));

	Group2D fpsgroup({ 5, 20, 0 });
	Label* fpscounter = new Label("100 FPS", { 0, 0, 400000.0f }, true);
	fpsgroup.submit(fpscounter);

	Label text("Hello, World!", { 400, 300, 50 });
	Font fnt("font.ttf", 50);
	
	GLint texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31
	};

	shader->bind();
	shader->setUniform1iv(shader->getUniformLocation("textures"), 32, texIDs);

	SoundManager::inst->add("mus.ogg");
	SoundHandle* handle = SoundManager::inst->get("mus.ogg")->genHandle();
	handle->play();

	FPSClock clock;
	Timer timer;
	while (!wnd.shouldClose()) {
		wnd.drawStart();

		renderer.begin();

		renderer.setColour({ 1, 1, 1, 1 });
		renderer.submit(&objects);

		renderer.setFont(nullptr);
		renderer.setColour({ 1, 1, 1, 0.5 });
		renderer.submit(&fpsgroup);

		float t = timer.elapsed();
		float r = clamp01(sinf(t));
		float g = clamp01(sinf(t + 2*pi/3));
		float b = clamp01(sinf(t + 4*pi/3));
		renderer.setColour({ r, g, b, 1 });
		renderer.setFont(&fnt);
		renderer.submit(&text);

		renderer.flushAll();

		wnd.drawEnd();

		if ((handle != nullptr) && (handle->stopped())) {
			delete handle;
			handle = nullptr;
		}

		printf("0x%x\n", handle);

		clock.tick();
		std::string fps = std::to_string((int)clock.getFPS());
		while (fps.length() < 5) {
			fps = " " + fps;
		}
		fpscounter->setString(fps + " FPS");
	}

	delete handle;
	SoundManager::inst->cleanup();

	return 0;
}
