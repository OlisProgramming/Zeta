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
#include "src\graphics\renderer\camera.h"
#include "src\level\level.h"
#include "src\level\global_data.h"
#include "src\entity\behaviours_builtin.h"
#include "src\entity\behaviour_factory.h"
#include "src\util\fps_clock.h"
#include "src\util\mathutil.h"
#include "src\sound\sound_manager.h"

int main(int argc, char* argv[]) {

#ifdef ZETA_CONFIG_RELEASE
# ifdef _WIN32
	FreeConsole();
# endif
#endif

	using namespace zeta;
	using namespace graphics;
	using namespace sound;
	using namespace util;
	using namespace entity;
	using namespace level;

	Window wnd("Zeta Engine", 800, 600);

	ShaderBasic* shader = new ShaderBasic;
	Renderer renderer(shader);
	Camera camera(shader, { 800, 600 });

	Label fpscounter("100 FPS", { 5, 20, 400000.0f }, true);

	ZETA_BEHAVIOUR_REGISTER(SpriteRenderBehaviour);

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
			input::InputInterface::inst->update();
			GlobalData::inst->totalTicks = ++ticks;
			level->tick();
		}

		camera.setX(elapsedTime * 30);
		camera.recomputeMatrices();

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
