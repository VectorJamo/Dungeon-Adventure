#include <iostream>

#include "GameState.h"
#include "../launcher/Display.h"

GameState::GameState(SDL_Renderer* renderer,  bool* gameStatus): StateManager(renderer, gameStatus), _tileMap(nullptr), _player(nullptr) {
	_tileMap = new Tilemap("res/maps/world.txt", _renderer);

	_player = new Player(49.5f * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 64, 64, "res/images/Soldier-Blue.png", _renderer, _tileMap);
}

GameState::~GameState() {
	delete _player;

	delete _tileMap;
}

void GameState::tick() {
	
	_player->tick();

}

void GameState::render() {
	_tileMap->render(_player->getXPos(), _player->getYPos(), 64, 64);
	_player->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight());
}
