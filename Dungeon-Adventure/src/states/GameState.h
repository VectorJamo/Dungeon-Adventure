#pragma once
#include "StateManager.h"
#include "../tilemap/Tilemap.h"
#include "../items/Player.h"

#include "../items/Torch.h"

class GameState: public StateManager {
private:
	Tilemap* _tileMap;
	
	// Entities
	Player* _player;

	// Game Objects
	Torch* _torch;

	std::vector<LightEmitter*> _lightEmitters;


public:
	GameState(SDL_Renderer* renderer, bool* gameStatus);
	~GameState();

	void tick() override;
	void render() override;
};

