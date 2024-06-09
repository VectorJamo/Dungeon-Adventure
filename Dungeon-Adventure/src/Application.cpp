#include "launcher/Game.h"

int main(int argc, char** argv) {

	Game* game = new Game(800, 600, "Dungeon Adventure");
	game->run();
	delete game;

	return 0;
}