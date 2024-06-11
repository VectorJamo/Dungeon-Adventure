#include <iostream>
#include <fstream>
#include <string>

#include "Tilemap.h"
#include "../utils/Macros.h"
#include "../launcher/Display.h"
#include "../effects/Light.h"

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
	_wall = IMG_LoadTexture(_renderer, "res/images/tiles/wall.png");
	SDL_SetTextureBlendMode(_wall, SDL_BLENDMODE_BLEND);
	ASSERT_CONDITIONAL(_wall == nullptr, "Failed to load wall image.");

	_floor = IMG_LoadTexture(_renderer, "res/images/tiles/floor.png");
	SDL_SetTextureBlendMode(_floor, SDL_BLENDMODE_BLEND);
	ASSERT_CONDITIONAL(_floor == nullptr, "Failed to load floor image.");
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


void Tilemap::render(int playerWorldX, int playerWorldY, int playerWidth, int playerHeight, const std::vector<LightEmitter*>& lightEmitters) {
	for (int i = 0; i < _mapRows; i++) {
		for (int j = 0; j < _mapCols; j++) {
			int tileWorldX = j * _tileSize;
			int tileWorldY = i * _tileSize;
			int tileScreenX = tileWorldX - ((playerWorldX + playerWidth / 2) - Display::getWidth() / 2);
			int tileScreenY = tileWorldY - ((playerWorldY + playerHeight / 2) - Display::getHeight() / 2);

			if (tileScreenX + _tileSize >= 0 && tileScreenX + _tileSize <= Display::getWidth() + _tileSize && 
				tileScreenY + _tileSize >= 0 && tileScreenY + _tileSize <= Display::getHeight() + _tileSize) {

				SDL_Rect dest = { tileScreenX, tileScreenY, _tileSize, _tileSize };

				// Calculate lighting
				// Light from the player
				float intensity = 20000 / pow(sqrt(pow((playerWorldX - tileWorldX), 2) + pow((playerWorldY - tileWorldY), 2)), 2);
				// Light from light emitting sources
				for (auto& emitter : lightEmitters) {
					intensity += emitter->intensityMultiplier / pow(sqrt(pow((emitter->lightPosX - tileWorldX), 2) + pow((emitter->lightPosY - tileWorldY), 2)), 2);
				}
				float alpha = intensity * 255;

				if (alpha < 50) {
					alpha = 50;
				}
				else if (alpha > 255) {
					alpha = 255;
				}

				if (_tileMap[i][j] == '1') {
					SDL_SetTextureAlphaMod(_wall, alpha);
					SDL_RenderCopy(_renderer, _wall, NULL, &dest);
				}
				else {
					SDL_SetTextureAlphaMod(_floor, alpha);
					SDL_RenderCopy(_renderer, _floor, NULL, &dest);
				}
			}
		}
	}

	for (int i = 0; i < _mapRows; i++) {
		for (int j = 0; j < _mapCols; j++) {
			int minimapWidth = _mapCols * 2;
			int minimapHeight = _mapRows * 2;

			SDL_Rect dest = { j * 2, i * 2, 2, 2 };
			if (_tileMap[i][j] == '1') {
				SDL_SetTextureAlphaMod(_wall, 255);
				SDL_RenderCopy(_renderer, _wall, NULL, &dest);
			}
			else {
				SDL_SetTextureAlphaMod(_floor, 255);
				SDL_RenderCopy(_renderer, _floor, NULL, &dest);
			}
		}
	}
	// Draw the player on the minimap
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	float playerWorldTileX = playerWorldX / _tileSize;
	float playerWorldTileY = playerWorldY / _tileSize;

	float playerPosXMinimap = playerWorldTileX * 2;
	float playerPosYMinimap = playerWorldTileY * 2;

	std::cout << playerWorldTileY << ", " << playerWorldTileY << std::endl;

	SDL_Rect rect = { playerPosXMinimap, playerPosYMinimap, 2, 2 };
	SDL_RenderFillRect(_renderer, &rect);
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
