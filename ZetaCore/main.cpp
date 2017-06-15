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
#include "src\level\level.h"
#include "src\level\global_data.h"
#include "src\entity\behaviours_builtin.h"
#include "src\util\fps_clock.h"
#include "src\util\mathutil.h"
#include "src\sound\sound_manager.h"

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;
	using namespace sound;
	using namespace util;
	using namespace entity;
	using namespace level;

	Window wnd("Zeta Engine", 800, 600);

	ShaderBasic* shader = new ShaderBasic;
	Renderer renderer(shader);
	shader->bind();
	glm::mat4 ortho = glm::ortho(0.0, 800.0, 600.0, 0.0, 0.1, 1000000.0);
	glm::mat4 view = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, -500000.0f));
	shader->setUniformMat4(shader->getUniformLocation("matProj"), ortho);
	shader->setUniformMat4(shader->getUniformLocation("matView"), view);

	Label fpscounter("100 FPS", { 5, 20, 400000.0f }, true);
	
	GLint texIDs[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10,11,12,13,14,15,16,17,18,19,
		20,21,22,23,24,25,26,27,28,29,
		30,31
	};

	shader->bind();
	shader->setUniform1iv(shader->getUniformLocation("textures"), 32, texIDs);


	///////

	Level* level = new Level("test.tmx");

	///////


	FPSClock clock;
	Timer timer;
	unsigned long ticks = 0L;
	float elapsedTime = 0.f;
	float lastElapsedTime = 0.f;
	while (!wnd.shouldClose()) {
		
		elapsedTime = timer.elapsed();

		GlobalData::inst->level = level;
		GlobalData::inst->totalTime = elapsedTime;
		GlobalData::inst->deltaTime = elapsedTime - lastElapsedTime;

		// Level tick
		float ticksShouldHaveDone = elapsedTime * 60.f;
		while (ticks < ticksShouldHaveDone) {
			GlobalData::inst->totalTicks = ++ticks;
			level->tick();
		}


		wnd.drawStart();
		renderer.begin();
		renderer.setColour({ 1, 1, 1, 1 });
		level->render(renderer);
		renderer.setColour({ 1, 1, 1, 0.5 });
		renderer.submit(&fpscounter);
		renderer.flushAll();
		wnd.drawEnd();

		clock.tick();
		std::string fps = std::to_string((int)clock.getFPS());
		while (fps.length() < 5) {
			fps = " " + fps;
		}
		fpscounter.setString(fps + " FPS");

		lastElapsedTime = elapsedTime;
	}

	delete level;

	return 0;
}
