#pragma once
#include <SDL.h>

class StateManager {
protected:
	SDL_Renderer* _renderer;

public:
	StateManager(SDL_Renderer* renderer);

	virtual void tick() = 0;
	virtual void render() = 0;

	void limitFps(int& lastTime, int fps);
};