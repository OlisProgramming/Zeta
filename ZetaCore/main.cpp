#include "src\game\game.h"
#include "src\entity\behaviour.h"
#include "src\entity\behaviours_builtin.h"
#include "src\entity\behaviour_factory.h"
#include "src\level\global_data.h"
#include "src\util\image_load.h"

using namespace zeta;
using namespace entity;

class PlayerBehaviour : public Behaviour {

public:
	ZETA_BEHAVIOUR_CLASS_BODY(PlayerBehaviour)

	PlayerBehaviour(Entity* parent) : Behaviour(parent) {
		parent->addBehaviour(new SpriteRenderBehaviour(parent, "test.png"));
	}

	void tick() override {
		glm::vec2 potentialMove = m_parent->getPos();
		glm::vec2 oldMove = m_parent->getPos();

		using namespace input;

		if (InputInterface::inst->keyDown(GLFW_KEY_LEFT)) {
			potentialMove.x -= 2;
		}
		if (InputInterface::inst->keyDown(GLFW_KEY_RIGHT)) {
			potentialMove.x += 2;
		}
		if (InputInterface::inst->keyDown(GLFW_KEY_UP)) {
			potentialMove.y -= 2;
		}
		if (InputInterface::inst->keyDown(GLFW_KEY_DOWN)) {
			potentialMove.y += 2;
		}

		m_parent->setPos(potentialMove);
		if (game::Game::inst->getLevel()->collideAll(m_parent)) {
			m_parent->setPos(oldMove);
		}

		//printf("%d %d\n", level::GlobalData::inst->levelTicks, level::GlobalData::inst->totalTicks);
		if (level::GlobalData::inst->levelTicks == 60) {
			if (game::Game::inst->getLevelName() == "test")
				game::Game::inst->changeLevel("test2");
			else
				game::Game::inst->changeLevel("test");
		}
	}
};

PlayerBehaviour* PlayerBehaviour::generate(Entity* parent, const std::vector<std::string>& params) {
	return new PlayerBehaviour(parent);
}

int main(int argc, char* argv[]) {

	zeta::game::Game game("Zeta Engine", 800, 600);
	
	// Register all custom behaviours
	ZETA_BEHAVIOUR_REGISTER(PlayerBehaviour);

	game.run("test");
	return 0;
}