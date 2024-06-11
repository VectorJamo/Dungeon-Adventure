#include <iostream>

#include "GameState.h"
#include "../launcher/Display.h"

#include "../effects/Light.h"

GameState::GameState(SDL_Renderer* renderer,  bool* gameStatus): StateManager(renderer, gameStatus), _tileMap(nullptr), _player(nullptr), _torch(nullptr) {
	_tileMap = new Tilemap("res/maps/world.txt", _renderer);

	_player = new Player(49.5f * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 64, 64, "res/images/Soldier-Blue.png", _renderer, _tileMap);
	_torch = new Torch(45 * _tileMap->getTileSize(), 40 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer);

	_lightEmitters.push_back(_torch);
}

GameState::~GameState() {
	delete _torch;
	delete _player;
	delete _tileMap;
}

void GameState::tick() {
	
	_player->tick();
	_torch->tick();
}

void GameState::render() {
	_tileMap->render(_player->getXPos(), _player->getYPos(), 64, 64, _lightEmitters);
	_player->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight());
	_torch->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight());
}
