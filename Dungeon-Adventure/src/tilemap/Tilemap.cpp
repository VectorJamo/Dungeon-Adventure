#include <iostream>
#include <fstream>
#include <string>

#include "Tilemap.h"
#include "../utils/Macros.h"
#include "../launcher/Display.h"

Tilemap::Tilemap(const char* mapPath, SDL_Renderer* renderer) {
	_renderer = renderer;

	_tileMap = nullptr;
	_wall = nullptr;
	_floor = nullptr;

	_tileMap = new unsigned char* [_mapRows];
	for (int i = 0; i < _mapRows; i++) {
		_tileMap[i] = new unsigned char[_mapCols];
	}

	loadTileMap(mapPath);
	
	// Load the assets
	_wall = IMG_LoadTexture(_renderer, "res/images/tiles/10.png");
	ASSERT_CONDITIONAL(_wall == nullptr, "Failed to load wall image.");

	_floor = IMG_LoadTexture(_renderer, "res/images/tiles/6.png");
	ASSERT_CONDITIONAL(_wall == nullptr, "Failed to load wall image.");
}

Tilemap::~Tilemap() {
	SDL_DestroyTexture(_floor);
	SDL_DestroyTexture(_wall);

	for (int i = 0; i < _mapRows; i++) {
		delete[] _tileMap[i];
	}
	delete[] _tileMap;
}

void Tilemap::tick() {
}

void Tilemap::render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight) {
	for (int i = 0; i < _mapRows; i++) {
		for (int j = 0; j < _mapCols; j++) {
			int tileWorldX = j * _tileSize;
			int tileWorldY = i * _tileSize;
			int tileScreenX = tileWorldX - ((playerWorldX + playerWidth / 2) - Display::getWidth() / 2);
			int tileScreenY = tileWorldY - ((playerWorldY + playerHeight / 2) - Display::getHeight() / 2);
			SDL_Rect src = { 0, 0, _tileSize, _tileSize }; 
			SDL_Rect dest = { tileScreenX, tileScreenY, _tileSize, _tileSize };
			if (_tileMap[i][j] == '1') {
				SDL_RenderCopy(_renderer, _wall, &src, &dest);
			}
			else {
				SDL_RenderCopy(_renderer, _floor, &src, &dest);
			}
		}
	}
}

void Tilemap::loadTileMap(const char* filePath) {
	std::ifstream stream(filePath);

	std::string line;
	int row = 0, col = 0;
	while (std::getline(stream, line)) {
		for (char& c : line) {
			if (c != '\t') {
				_tileMap[row][col] = c;
				col++;
			}
		}
		row++;
		col = 0;
	}

	stream.close();
}
