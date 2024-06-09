#include "StateManager.h"

StateManager::StateManager(SDL_Renderer* renderer):_renderer(renderer) {
}

void StateManager::limitFps(int& lastTime, int fps) {
	float deltaTime = SDL_GetTicks() - lastTime; // Returns frame time in miliseconds
	if (deltaTime < (1000 / fps)) { // 1sec = 1000msc
		SDL_Delay((1000 / fps) - deltaTime);
	}
}
