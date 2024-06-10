#pragma once
#include <SDL.h>

class StateManager {
protected:
	SDL_Renderer* _renderer;
	static StateManager* _currentState;

	bool* _gameStatus;

public:
	StateManager(SDL_Renderer* renderer, bool* gameStatus);

	virtual void tick() = 0;
	virtual void render() = 0;

	static void SetCurrentState(StateManager* state);

	void limitFps(int& lastTime, int fps);

	static inline StateManager* GetCurrentState() { return _currentState; }
};