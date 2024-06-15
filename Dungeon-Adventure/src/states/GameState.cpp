#include <iostream>

#include "GameState.h"
#include "../launcher/Display.h"

#include "../gui/GUI_Manager.h"

#define VERSION "alpha v0.1"

int GameState::_points;
GameState::GameState(SDL_Renderer* renderer,  bool* gameStatus): StateManager(renderer, gameStatus), _tileMap(nullptr), _player(nullptr) {
	srand(time(NULL));

	_tileMap = new Tilemap("res/maps/world.txt", _renderer);

	// Player Entity
	_player = new Player(49.5f * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 64, 64, "res/images/Soldier-Blue.png", _renderer, _tileMap, "player");
	_points = 0;
	_pointsText = "Points: " + std::to_string(_points);

	_fontExtraLarge = new gui::Font("res/fonts/roboto/Roboto-Regular.ttf", 56);
	_fontLarge = new gui::Font("res/fonts/roboto/Roboto-Regular.ttf", 48);
	_fontMedium = new gui::Font("res/fonts/roboto/Roboto-Regular.ttf", 32);
	_fontSmall = new gui::Font("res/fonts/roboto/Roboto-Regular.ttf", 18);

	_fontLargeLight = new gui::Font("res/fonts/roboto/Roboto-Light.ttf", 48);
	_fontMediumLight = new gui::Font("res/fonts/roboto/Roboto-Light.ttf", 32);
	_fontSmallLight = new gui::Font("res/fonts/roboto/Roboto-Light.ttf", 18);
	
	// Game Objects
	_torches.reserve(100);
	_torches.emplace_back(new Torch(49 * _tileMap->getTileSize(), 45 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(50 * _tileMap->getTileSize(), 45 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));

	_torches.emplace_back(new Torch(29 * _tileMap->getTileSize(), 37 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(29 * _tileMap->getTileSize(), 46 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(31 * _tileMap->getTileSize(), 15 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(31 * _tileMap->getTileSize(), 30 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(37 * _tileMap->getTileSize(), 34 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(16 * _tileMap->getTileSize(), 42 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(82 * _tileMap->getTileSize(), 28 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(74 * _tileMap->getTileSize(), 16 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(56 * _tileMap->getTileSize(), 62 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(65 * _tileMap->getTileSize(), 69 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	_torches.emplace_back(new Torch(58 * _tileMap->getTileSize(), 76 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));

	for (int i = 1; i < 10; i++) {
		_torches.emplace_back(new Torch(50 * _tileMap->getTileSize(), i * 10 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
		_torches.emplace_back(new Torch(i * 10 * _tileMap->getTileSize(), 50 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));

		_torches.emplace_back(new Torch(10*i * _tileMap->getTileSize(), 9 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
		_torches.emplace_back(new Torch(10*i * _tileMap->getTileSize(), 90 * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
		_torches.emplace_back(new Torch(9 * _tileMap->getTileSize(), 10*i * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
		_torches.emplace_back(new Torch(90 * _tileMap->getTileSize(), 10 * i * _tileMap->getTileSize(), 64, 64, "res/images/tiles/torch-sprite.png", _renderer, "torch"));
	}

	for (Torch* torch : _torches)
		_lightEmitters.push_back(torch);

	_map = new Map(42 * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 32, 32, "res/images/map.png", _renderer, "map");

	_spikes.emplace_back(new Spike(40 * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 32, 32, "res/images/spike-sprite.png", _renderer, "spike"));

	_roaches.reserve(5);
	_roaches.push_back(new Cockroach(56 * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 22, 22, "res/images/roach.png", _renderer, _tileMap, "roach"));
	_roaches.push_back(new Cockroach(56 * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 22, 22, "res/images/roach.png", _renderer, _tileMap, "roach"));
	_roaches.push_back(new Cockroach(56 * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 22, 22, "res/images/roach.png", _renderer, _tileMap, "roach"));
	_roaches.push_back(new Cockroach(56 * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 22, 22, "res/images/roach.png", _renderer, _tileMap, "roach"));
	_roaches.push_back(new Cockroach(56 * _tileMap->getTileSize(), 47 * _tileMap->getTileSize(), 22, 22, "res/images/roach.png", _renderer, _tileMap, "roach"));

	_gameObjects.push_back(_map);

	for (auto& spike : _spikes)
		_gameObjects.push_back(spike);

	for(auto& roach: _roaches)
		_entities.push_back(roach);

	// UI
	_versionLabel = new gui::Label(0, 0, VERSION, _fontSmall, _renderer);
	_versionLabel->setTextColor(255, 255, 255, 255);
	_versionLabel->setPosition(Display::getWidth() - _versionLabel->getWidth() - 10, Display::getHeight() - _versionLabel->getHeight() - 10);
	
	_pointsLabel = new gui::Label(0, 0, _pointsText.c_str(), _fontSmall, _renderer);
	_pointsLabel->setPosition(Display::getWidth() - 1.5*_pointsLabel->getWidth(), 10);

	_showMiniMap = false;
	_takeInput = true;
}

GameState::~GameState() {
	for (auto& gameObject : _gameObjects)
		delete gameObject;

	for (Torch* torch : _torches)
		delete torch;

	delete _player;
	delete _tileMap;
}

void GameState::tick() {
	_pointsText = "Points: " + std::to_string(_points);

	// Update the map
	_map->tick();

	// Update gameObjects
	for(Torch* torch: _torches)
		torch->tick();
	
	for (auto* spike : _spikes)
		spike->tick();

	// Update the entities
	_player->tick(_gameObjects, _entities);
	for (auto& entity : _entities)
		entity->tick();
	
	_pointsLabel->setText(_pointsText.c_str());
	gui::GUI_Manager::UpdateTempTexts();
}

void GameState::render() {
	// Render the tilemap
	_tileMap->render(_player->getXPos(), _player->getYPos(), 64, 64, _lightEmitters);

	// Render the game objects
	for(Torch* torch: _torches)
		torch->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight());
	
	if(!_player->_hasMap)
		_map->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight(), _lightEmitters);
	
	for(auto& spike: _spikes)
		spike->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight(), _lightEmitters);
	
	// Render the entities
	for (auto& entity : _entities)
		entity->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight(), _lightEmitters);

	if (_showMiniMap)
		_tileMap->renderMinimap(_player->getXPos(), _player->getYPos());

	_player->render(_player->getXPos(), _player->getYPos(), _player->getWidth(), _player->getHeight());
	
	// UI
	_versionLabel->render();
	_pointsLabel->render();
	gui::GUI_Manager::RenderTempTexts();
}

void GameState::handleInput(SDL_Event& ev) {
	if (ev.type == SDL_KEYDOWN) {
		if (ev.key.keysym.sym == SDLK_m && _takeInput && _player->_hasMap ) {
			_takeInput = false;
			_showMiniMap = !_showMiniMap;
		}
	}

	if (ev.type == SDL_KEYUP) {
		if (ev.key.keysym.sym == SDLK_m) {
			_takeInput = true;
		}

	}
}

void GameState::setPoints(int points) {
	_points = points;
}
