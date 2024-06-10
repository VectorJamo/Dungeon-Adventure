#include "StateManager.h"

StateManager* StateManager::_currentState = nullptr;

StateManager::StateManager(SDL_Renderer* renderer, bool* gameStatus):_renderer(renderer), _gameStatus(gameStatus) {
}

void StateManager::limitFps(int& lastTime, int fps) {
	float deltaTime = SDL_GetTicks() - lastTime; // Returns frame time in miliseconds
	if (deltaTime < (1000 / fps)) { // 1sec = 1000msc
		SDL_Delay((1000 / fps) - deltaTime);
	}
}

void StateManager::SetCurrentState(StateManager* state) {
	if (_currentState == nullptr) {
		_currentState = state;
		return;
	}
	delete _currentState;
	_currentState = state;
}
