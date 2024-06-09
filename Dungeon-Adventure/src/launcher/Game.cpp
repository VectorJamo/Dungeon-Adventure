#include "Game.h"

bool Game::running;
Game::Game(int width, int height, const char* title) {
	_display = new Display(width, height, title);
	running = true;

	_activeState = new MenuState(_display->getRendererInstance());
}

Game::~Game() {
	delete _activeState;

	delete _display;
}

void Game::run() {
	while (running) {
		int lastTime = SDL_GetTicks();
		
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				running = false;
		}

		_display->clear(0, 0, 0, 255);

		_activeState->tick();

		_activeState->render();

		_display->show();

		_activeState->limitFps(lastTime, 60);
	}
}
