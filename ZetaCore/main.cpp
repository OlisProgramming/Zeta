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

#include <ft2build.h>
#include <freetype\freetype.h>
#include <freetype-gl.h>
#include <gorilla\ga.h>
#include <gorilla\gau.h>

#if 0

int main(int argc, char* argv[]) {

	using namespace zeta;
	using namespace graphics;
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

	bool a = false;

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

		clock.tick();
		std::string fps = std::to_string((int)clock.getFPS());
		while (fps.length() < 5) {
			fps = " " + fps;
		}
		fpscounter->setString(fps + " FPS");
	}

	return 0;
}

#else

static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}

int main()
{
	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_Sound* sound;
	ga_Handle* handle;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 1;
	gc_int32 quit = 0;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);

	/* Create and play shared sound */
	if (!loop)
		pLoopSrc = 0;
	sound = gau_load_sound_file("../res/sound/mus.ogg", "ogg");
	handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
	ga_handle_play(handle);

	/* Bounded mix/queue/dispatch loop */
	while (!quit)
	{
		gau_manager_update(mgr);
		printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
		gc_thread_sleep(1);
	}

	/* Clean up sound */
	ga_sound_release(sound);

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();

	return 0;
}

#endif
