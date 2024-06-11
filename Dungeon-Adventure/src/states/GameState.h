#pragma once
#include "StateManager.h"
#include "../tilemap/Tilemap.h"
#include "../items/Player.h"

class GameState: public StateManager {
private:
	Tilemap* _tileMap;

	Player* _player;

public:
	GameState(SDL_Renderer* renderer, bool* gameStatus);
	~GameState();

	void tick() override;
	void render() override;
};

