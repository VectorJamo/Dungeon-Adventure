#pragma once
#include "StateManager.h"

#include "../tilemap/Tilemap.h"

#include "../items/Player.h"
#include "../items/Torch.h"
#include "../items/PickupMap.h"
#include "../items/Spike.h"
#include "../items/Cockroach.h"

#include"../gui/Label.h"
#include "../effects/Light.h"
#include "../items/GameObject.h"

#include <vector>
#include <string>

class GameState: public StateManager {
private:
	Tilemap* _tileMap;
	
	// Entities
	Player* _player;

	// Game Objects
	std::vector<LightEmitter*> _lightEmitters;
	std::vector<GameObject*> _gameObjects;
	std::vector<Entity*> _entities;

	std::vector<Torch*> _torches;
	std::vector<Spike*> _spikes;
	Map* _map;
	std::vector<Cockroach*> _roaches;
	
	// UI
	gui::Font *_fontExtraLarge, *_fontLarge, *_fontMedium, *_fontSmall;
	gui::Font *_fontLargeLight, *_fontMediumLight, *_fontSmallLight;

	gui::Label* _versionLabel;

	bool _showMiniMap;
	bool _takeInput;
	
	std::string _pointsText;
	static int _points;
	gui::Label* _pointsLabel;

public:
	GameState(SDL_Renderer* renderer, bool* gameStatus);
	~GameState();

	void tick() override;
	void render() override;
	void handleInput(SDL_Event& ev) override;

	static void setPoints(int points);
	static inline int getPoints() { return _points; }
};

