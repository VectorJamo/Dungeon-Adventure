#include <iostream>
#include <fstream>
#include <string>

#include "Tilemap.h"
#include "../utils/Macros.h"
#include "../launcher/Display.h"

int Tilemap::_mapRows;
int Tilemap::_mapCols;
int Tilemap::_tileSize;

Tilemap::Tilemap(const char* mapPath, const char* spritePath, int mapRows, int mapCols, int tileSize, SDL_Renderer* renderer) {
	_renderer = renderer;
	_mapRows = mapRows;
	_mapCols = mapCols;
	_tileSize = tileSize;

	_tileMap = nullptr;
	_mapSprite = nullptr;

	_tileMap = new unsigned char* [mapRows];
	for (int i = 0; i < mapRows; i++) {
		_tileMap[i] = new unsigned char[mapCols];
	}

	loadTileMap(mapPath);
	_mapSprite = IMG_LoadTexture(_renderer, spritePath);
	
	ASSERT_CONDITIONAL(_mapSprite == nullptr, "Failed to load map sprite texture.");
}

Tilemap::~Tilemap() {
	for (int i = 0; i < _mapRows; i++) {
		delete[] _tileMap[i];
	}
	delete[] _tileMap;

	SDL_DestroyTexture(_mapSprite);
}

void Tilemap::tick() {
}

void Tilemap::render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight) {
	for (int i = 0; i < _mapRows; i++) {
		for (int j = 0; j < _mapCols; j++) {
			if (_tileMap[i][j] != '0') {
				int tileWorldX = j * _tileSize;
				int tileWorldY = i * _tileSize;
				int tileScreenX = tileWorldX - ((playerWorldX + playerWidth / 2) - Display::getWidth() / 2);
				int tileScreenY = tileWorldY - ((playerWorldY + playerHeight / 2) - Display::getHeight() / 2);

				SDL_Rect src = { 0, 0, _tileSize, _tileSize }; // TODO: Modify the src if using a spritesheet
				SDL_Rect dest = { tileScreenX, tileScreenY, _tileSize, _tileSize };

				SDL_RenderCopy(_renderer, _mapSprite, &src, &dest);
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
