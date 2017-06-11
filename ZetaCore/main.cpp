#include <stdio.h>
#include <stdlib.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "src\graphics\window.h"
#include "src\graphics\renderer\renderer.h"
#include "src\graphics\renderable\group.h"
#include "src\graphics\renderable\sprite.h"
#include "src\graphics\renderable\label.h"
#include "src\graphics\texture\texture_manager.h"
#include "src\graphics\font\font_manager.h"
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

	ShaderBasic* shader = new ShaderBasic;
	Renderer renderer(shader);
	shader->bind();
	glm::mat4 ortho = glm::ortho(0.0, 800.0, 600.0, 0.0, 0.1, 1000000.0);
	glm::mat4 view = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -500000.0f));
	shader->setUniformMat4(shader->getUniformLocation("matProj"), ortho);
	shader->setUniformMat4(shader->getUniformLocation("matView"), view);

	Group objects({0, 0, 0});
	objects.submit(new Sprite(glm::vec3(32, 32, 0), "testa.png", false));
	objects.submit(new Sprite(glm::vec3(800-32, 32, 0), "test.png", false));
	objects.submit(new Sprite(glm::vec3(800-32, 600-32, 0), "testa.png", false));
	objects.submit(new Sprite(glm::vec3(32, 600-32, 0), "test.png", false));

	Group fpsgroup({ 5, 20, 0 });
	Label* fpscounter = new Label("100 FPS", { 0, 0, 400000.0f }, true);
	fpsgroup.submit(fpscounter);

	Label text("Hello, World!", { 400, 300, 50 }, false);
	FontManager::inst->add("font.ttf", 50);
	glm::vec2 a(FontManager::inst->getTextWidth("font.ttf", 50, "Hello, World!") / 2.f, -25);
	printf("%f, %f\n", a.x, a.y);
	text.setPivot(a);
	
	GLint texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31
	};

	shader->bind();
	shader->setUniform1iv(shader->getUniformLocation("textures"), 32, texIDs);

	FPSClock clock;
	Timer timer;
	while (!wnd.shouldClose()) {
		float t = timer.elapsed();
		wnd.drawStart();

		renderer.begin();

		renderer.setColour({ 1, 1, 1, 1 });
		renderer.submit(&objects);

		renderer.setFont(nullptr);
		renderer.setColour({ 1, 1, 1, 0.5 });
		renderer.submit(&fpsgroup);

		float r = clamp01(sinf(t));
		float g = clamp01(sinf(t + 2*pi/3));
		float b = clamp01(sinf(t + 4*pi/3));
		renderer.setColour({ r, g, b, 1 });
		renderer.setFont("font.ttf", 50);
		text.setScaleX(sinf(t));
		text.setScaleY(cosf(t));
		renderer.submit(&text);

		renderer.flushAll();

		wnd.drawEnd();

		clock.tick();
		std::string fps = std::to_string((int)clock.getFPS());
		while (fps.length() < 5) {
			fps = " " + fps;
		}
		fpscounter->setString(fps + " FPS");
	}

	return 0;
}
