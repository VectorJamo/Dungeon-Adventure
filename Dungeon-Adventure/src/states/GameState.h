#pragma once
#include "StateManager.h"

class GameState: public StateManager {
private:
	int x;

public:
	GameState(SDL_Renderer* renderer);
	~GameState();

	void tick() override;
	void render() override;
};

