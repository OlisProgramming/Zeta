#include "src\game\game.h"
#include "src\entity\behaviour.h"
#include "src\entity\behaviour_factory.h"
#include "src\util\image_load.h"

using namespace zeta;
using namespace entity;

class ImmediateWarpBehaviour : public Behaviour {

private:
	std::string m_levelName;

public:
	ZETA_BEHAVIOUR_CLASS_BODY(ImmediateWarpBehaviour)

	ImmediateWarpBehaviour(Entity* parent, const std::string& levelName) : m_levelName(levelName), Behaviour(parent) {
	}

	void tick() override {
		game::Game::inst->changeLevel(m_levelName);
	}
};

ImmediateWarpBehaviour* ImmediateWarpBehaviour::generate(Entity* parent, const std::vector<std::string>& params) {
	return new ImmediateWarpBehaviour(parent, params[0]);
}

int main(int argc, char* argv[]) {

	zeta::game::Game game("Zeta Engine", 800, 600);
	
	// Register all custom behaviours
	ZETA_BEHAVIOUR_REGISTER(ImmediateWarpBehaviour);

	game.run("test");
	return 0;
}