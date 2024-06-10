#pragma once
#include "StateManager.h"

class GameState: public StateManager {
private:

public:
	GameState(SDL_Renderer* renderer, bool* gameStatus);
	~GameState();

	void tick() override;
	void render() override;
};

