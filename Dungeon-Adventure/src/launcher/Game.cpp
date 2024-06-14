#include "Game.h"

#include "../gui/GUI_Manager.h"

bool Game::running;
Game::Game(int width, int height, const char* title) {
	_display = new Display(width, height, title);
	running = true;

	StateManager::SetCurrentState(new MenuState(_display->getRendererInstance(), &running));
}

Game::~Game() {
	delete _display;
}

void Game::run() {
	while (running) {
		int lastTime = SDL_GetTicks();
		
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				running = false;

			gui::GUI_Manager::Update(ev);

			StateManager::GetCurrentState()->handleInput(ev);
		}

		_display->clear(0, 0, 0, 255);

		StateManager::GetCurrentState()->tick();
		StateManager::GetCurrentState()->render();

		_display->show();

		StateManager::GetCurrentState()->limitFps(lastTime, 60);
	}
}
