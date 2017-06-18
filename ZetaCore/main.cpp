#include "src\game\game.h"

int main(int argc, char* argv[]) {

	zeta::game::Game game("Zeta Engine", 800, 600);
	game.run("test");
	return 0;
}