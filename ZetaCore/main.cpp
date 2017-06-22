#include "src\game\game.h"
#include "src\entity\behaviour.h"
#include "src\entity\behaviours_builtin.h"
#include "src\entity\behaviour_factory.h"
#include "src\level\global_data.h"
#include "src\util\image_load.h"
#include "src\graphics\renderable\line.h"

using namespace zeta;
using namespace entity;

class PlayerBehaviour : public Behaviour {

private:
	Line* m_line;

public:
	ZETA_BEHAVIOUR_CLASS_BODY(PlayerBehaviour)

	PlayerBehaviour(Entity* parent) : Behaviour(parent) {
		parent->addBehaviour(new SpriteRenderBehaviour(parent, "test.png"));
		parent->addBehaviour(new TextRenderBehaviour(parent, "Hello, World!", "consola.ttf", 15));
		m_line = new Line(glm::vec2(5, 5), glm::vec2(795, 595), -50, 5);
	}

	PlayerBehaviour::~PlayerBehaviour() {
		delete m_line;
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

		m_line->update(m_parent->getPos2(), glm::vec2(795, 595), -50, 5);
	}

	void render(Renderer& renderer) override {

		renderer.setColour({ 1, 1, 1, 1 });
		renderer.submit(m_line);
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